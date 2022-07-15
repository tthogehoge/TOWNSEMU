/* LICENSE>>
Copyright 2020 Soji Yamakawa (CaptainYS, http://www.ysflight.com)

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

<< LICENSE */
#include <iostream>

#include "cpputil.h"
#include "diskdrive.h"
#include "vmbase.h"


void DiskDrive::ImageFile::SaveIfModified(void)
{
	if(true==d77.IsModified())
	{
		std::vector <unsigned char> bin;
		switch(fileType)
		{
		case IMGFILE_RAW:
			bin=d77.MakeRawImage();
			break;
		case IMGFILE_D77:
			bin=d77.MakeD77Image();
			break;
		}
		if(0<bin.size())
		{
			if(true!=cpputil::WriteBinaryFile(fName,bin.size(),bin.data()))
			{
				std::cout << "Warning!  Floppy Disk Image could not be saved." << std::endl;
			}
			else
			{
				std::cout << "Auto-saved disk image:" << fName << std::endl;
			}
		}
	}

	for(int i=0; i<d77.GetNumDisk(); ++i)
	{
		d77.GetDisk(i)->ClearModified();
	}
}

bool DiskDrive::ImageFile::LoadD77orRAW(std::string fName)
{
	auto ext=cpputil::GetExtension(fName);
	cpputil::Capitalize(ext);
	if(true==IsD77Extension(ext))
	{
		return LoadD77(fName);
	}
	else
	{
		return LoadRAW(fName);
	}
}
bool DiskDrive::ImageFile::LoadD77(std::string fName)
{
	bool verbose=false;
	auto bin=cpputil::ReadBinaryFile(fName);
	if(0==bin.size())
	{
		return false;
	}

	this->d77.CleanUp();
	this->d77.SetData(bin,verbose);
	if(0<this->d77.GetNumDisk())
	{
		this->fileType=IMGFILE_D77;
		this->fName=fName;
		return true;
	}
	else
	{
		return false;
	}
}
bool DiskDrive::ImageFile::LoadRAW(std::string fName)
{
	bool verbose=false;
	auto bin=cpputil::ReadBinaryFile(fName);
	if(0==bin.size())
	{
		return false;
	}

	this->d77.CleanUp();
	if(true==this->d77.SetRawBinary(bin,verbose))
	{
		this->fileType=IMGFILE_RAW;
		this->fName=fName;
		return true;
	}
	else
	{
		return false;
	}
}

////////////////////////////////////////////////////////////

void DiskDrive::State::Reset(void)
{
	for(auto &d : drive)
	{
		d.trackPos=0;      // Actual head location.
		d.trackReg=0;      // Value in track register 0202H
		d.sectorReg=1;     // Value in sector register 0x04H
		d.dataReg=0;       // Value in data register 0x06H
		d.lastSeekDir=1;
		d.motor=false;
		d.diskChange=false;
		d.pretendDriveNotReadyCount=0;
	}
	driveSwitch=false;
	driveSelectBit=1;      // Looks like A drive is selected by default.
	side=0;
	busy=false;
	MODEB=false;
	HISPD=false;
	INUSE=false;
	lastCmd=0;
	lastStatus=0;

	CLKSEL=false;
	DDEN=false;
	IRQMSK=true;

	recordType=false;
	recordNotFound=false;
	CRCError=false;
	lostData=false;
	writeFault=false;

	addrMarkReadCount=0;

	data.clear();
	dataReadPointer=0;
	expectedWriteLength=0;
	DRQ=false;
	IRQ=false;
}

void DiskDrive::State::Drive::DiskChanged(void)
{
	diskChange=true;
	pretendDriveNotReadyCount=1;
}

////////////////////////////////////////////////////////////

/* static */ bool DiskDrive::IsD77Extension(std::string ext)
{
	return ".D77"==ext || ".D88"==ext;
}

DiskDrive::DiskDrive(VMBase *vmPtr) : Device(vmPtr)
{
	Reset();
	for(auto &d : state.drive)
	{
		d.imgFileNum=-1;
		d.diskIndex=-1;
		d.mediaType=MEDIA_UNKNOWN;
	}
	for(auto &i : imgFile)
	{
		i.fileType=IMGFILE_RAW;
	}
}

bool DiskDrive::LoadD77orRAW(unsigned int driveNum,const char fNameIn[],bool verbose)
{
	auto ext=cpputil::GetExtension(fNameIn);
	cpputil::Capitalize(ext);
	if(true==IsD77Extension(ext))
	{
		return LoadD77(driveNum,fNameIn,verbose);
	}
	else
	{
		return LoadRawBinary(driveNum,fNameIn,verbose);
	}
}

bool DiskDrive::LoadD77(unsigned int driveNum,const char fNameIn[],bool verbose)
{
	driveNum&=3;
	auto imgIdx=driveNum;

	SaveIfModifiedAndUnlinkDiskImage(imgIdx);

	auto fName=cpputil::FindFileWithSearchPaths(fNameIn,searchPaths);
	if(true==imgFile[imgIdx].LoadD77(fName))
	{
		LinkDiskImageToDrive(imgIdx,0,driveNum);
		return true;
	}
	return false;
}

bool DiskDrive::LoadRawBinary(unsigned int driveNum,const char fNameIn[],bool verbose)
{
	driveNum&=3;
	auto imgIdx=driveNum;

	SaveIfModifiedAndUnlinkDiskImage(imgIdx);

	auto fName=cpputil::FindFileWithSearchPaths(fNameIn,searchPaths);
	if(true==imgFile[imgIdx].LoadRAW(fName))
	{
		LinkDiskImageToDrive(imgIdx,0,driveNum);
		return true;
	}
	return false;
}

void DiskDrive::LinkDiskImageToDrive(int imgIdx,int diskIdx,int driveNum)
{
	state.drive[driveNum].imgFileNum=imgIdx;
	state.drive[driveNum].diskIndex=diskIdx;
	state.drive[driveNum].mediaType=IdentifyDiskMediaType(imgFile[imgIdx].d77.GetDisk(diskIdx));
	state.drive[driveNum].DiskChanged();
}

void DiskDrive::SaveIfModifiedAndUnlinkDiskImage(unsigned int imgIndex)
{
	// First unlink any drive pointing to the disk image
	for(auto &d : state.drive)
	{
		if(d.imgFileNum==imgIndex)
		{
			d.imgFileNum=-1;
			d.diskIndex=-1;
			d.mediaType=MEDIA_UNKNOWN;
		}
	}
	imgFile[imgIndex].SaveIfModified();
}

void DiskDrive::Eject(unsigned int driveNum)
{
	state.drive[driveNum].imgFileNum=-1;
	state.drive[driveNum].diskIndex=-1;
	state.drive[driveNum].mediaType=MEDIA_UNKNOWN;
}

D77File::D77Disk *DiskDrive::GetDriveDisk(int driveNum)
{
	if(0<=driveNum && driveNum<NUM_DRIVES)
	{
		auto &drv=state.drive[driveNum];
		if(0<=drv.imgFileNum && drv.imgFileNum<NUM_DRIVES)
		{
			return imgFile[drv.imgFileNum].d77.GetDisk(drv.diskIndex);
		}
	}
	return nullptr;
}
const D77File::D77Disk *DiskDrive::GetDriveDisk(int driveNum) const
{
	if(0<=driveNum && driveNum<NUM_DRIVES)
	{
		auto &drv=state.drive[driveNum];
		if(0<=drv.imgFileNum && drv.imgFileNum<NUM_DRIVES)
		{
			return imgFile[drv.imgFileNum].d77.GetDisk(drv.diskIndex);
		}
	}
	return nullptr;
}
DiskDrive::ImageFile *DiskDrive::GetDriveImageFile(int driveNum)
{
	if(0<=driveNum && driveNum<NUM_DRIVES)
	{
		auto &drv=state.drive[driveNum];
		if(0<=drv.imgFileNum && drv.imgFileNum<NUM_DRIVES)
		{
			return &imgFile[drv.imgFileNum];
		}
	}
	return nullptr;
}
const DiskDrive::ImageFile *DiskDrive::GetDriveImageFile(int driveNum) const
{
	if(0<=driveNum && driveNum<NUM_DRIVES)
	{
		auto &drv=state.drive[driveNum];
		if(0<=drv.imgFileNum && drv.imgFileNum<NUM_DRIVES)
		{
			return &imgFile[drv.imgFileNum];
		}
	}
	return nullptr;
}

void DiskDrive::SaveModifiedDiskImages(void)
{
	for(auto &img : imgFile)
	{
		img.SaveIfModified();
	}
}

void DiskDrive::SetWriteProtect(int driveNum,bool writeProtect)
{
	auto diskPtr=GetDriveDisk(driveNum);
	if(nullptr!=diskPtr)
	{
		// Change of write-protection is not a modification for RAW image.
		// Write-protection is a flag in .D77.
		// Therefore, when it is a RAW image, it shouldn't change the modified flag.
		bool isModified=diskPtr->IsModified();
		if(true==writeProtect)
		{
			diskPtr->SetWriteProtected();
		}
		else
		{
			diskPtr->ClearWriteProtected();
		}
		auto imgFilePtr=GetDriveImageFile(driveNum);
		if(nullptr!=imgFilePtr && IMGFILE_RAW==imgFilePtr->fileType)
		{
			if(true!=isModified)
			{
				diskPtr->ClearModified();
			}
		}
	}
}

unsigned int DiskDrive::IdentifyDiskMediaType(const D77File::D77Disk *diskPtr) const
{
	unsigned int totalSize=0;
	for(auto loc : diskPtr->AllTrack())
	{
		auto trk=diskPtr->GetTrack(loc.track,loc.side);
		for(auto &sec : trk->sector)
		{
			totalSize+=(128<<sec.sizeShift);
		}
	}
	totalSize/=1024;
	unsigned int mediaType=MEDIA_UNKNOWN;
	if(totalSize<600)
	{
		return MEDIA_2D;
	}
	else if(600<=totalSize && totalSize<680)
	{
		return MEDIA_2DD_640KB;
	}
	else if(680<=totalSize && totalSize<760)
	{
		return MEDIA_2DD_720KB;
	}
	else if(1200<=totalSize && totalSize<1300)
	{
		return MEDIA_2HD_1232KB;
	}
	else if(1400<=totalSize && totalSize<1500)
	{
		return MEDIA_2HD_1440KB;
	}
	return MEDIA_UNKNOWN;
}

unsigned int DiskDrive::IdentifyDiskMediaTypeFromTrackCapacity(unsigned int trackCapacity) const
{
	// [10]
	//   1232KB format 1024 bytes per sector,  8 sectors per track, 77 tracks
	//   1440KB format  512 bytes per sector, 18 sectors per track, 80 tracks
	//    640KB format  512 bytes per sector,  8 sectors per track, 80 tracks
	//    720KB format  512 bytes per sector,  9 sectors per track, 80 tracks
	if(1024*8==trackCapacity)
	{
		return MEDIA_2HD_1232KB;
	}
	else if(512*18==trackCapacity)
	{
		return MEDIA_2HD_1440KB;
	}
	else if(512*8==trackCapacity)
	{
		return MEDIA_2DD_640KB;
	}
	else if(512*9==trackCapacity)
	{
		return MEDIA_2DD_720KB;
	}
	return MEDIA_UNKNOWN;
}

////////////////////////////////////////////////////////////


void DiskDrive::SendCommand(unsigned int cmd,uint64_t vmTime)
{
	if(0xFE==cmd)
	{
		// Meaning of 0xFE is unknown.
		// MB8877 Data sheet does not list this command.
		// Should I take it as 0xDE?
		state.lastStatus=MakeUpStatus(0xD0);
	}
	else if((cmd&0xF0)!=0xD0 && 0==state.driveSelectBit)
	{
		// Drive not selected.
		return;
	}
	else
	{
		state.data.clear();
		state.dataReadPointer=0;

		auto &drv=state.drive[DriveSelect()];
		switch(cmd&0xF0)
		{
		case 0x00: // Restore
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+RESTORE_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.CRCErrorAfterRead=false;
			state.busy=true;
			break;
		case 0x10: // Seek
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+SEEK_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.CRCErrorAfterRead=false;
			state.busy=true;
			break;
		case 0x20: // Step?
		case 0x30: // Step?
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+STEP_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.CRCErrorAfterRead=false;
			state.busy=true;
			break;
		case 0x40: // Step In
		case 0x50: // Step In
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+STEP_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.CRCErrorAfterRead=false;
			state.busy=true;
			break;
		case 0x60: // Step Out
		case 0x70: // Step Out
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+STEP_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.CRCErrorAfterRead=false;
			state.busy=true;
			break;

		case 0x80: // Read Data (Read Sector)
		case 0x90: // Read Data (Read Sector)
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+SECTOR_READ_WRITE_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.busy=true;

			state.data.clear();
			state.dataReadPointer=0;
			state.DRQ=false;
			state.IRQ=false;
			state.CRCErrorAfterRead=false;
			break;
		case 0xA0: // Write Data (Write Sector)
		case 0xB0: // Write Data (Write Sector)
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+SECTOR_READ_WRITE_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.busy=true;

			state.data.clear();
			state.expectedWriteLength=0;
			state.DRQ=false;
			state.IRQ=false;
			state.CRCErrorAfterRead=false;
			break;

		case 0xC0: // Read Address
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+ADDRMARK_READ_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			state.busy=true;

			state.data.clear();
			state.dataReadPointer=0;
			state.DRQ=false;
			state.IRQ=false;
			state.CRCErrorAfterRead=false;
			break;
		case 0xE0: // Read Track
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			std::cout << __FUNCTION__ << std::endl;
			std::cout << "Command " << cpputil::Ubtox(cmd) << " not supported yet." << std::endl;

			state.data.clear();
			state.dataReadPointer=0;
			state.DRQ=false;
			state.IRQ=false;
			state.CRCErrorAfterRead=false;
			break;
		case 0xF0: // Write Track
			vmPtr->ScheduleDeviceCallBack(*this,vmTime+WRITE_TRACK_TIME);
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;

			state.data.clear();
			state.expectedWriteLength=0;
			state.DRQ=false;
			state.IRQ=false;
			state.CRCErrorAfterRead=false;
			break;

		case 0xD0: // Force Interrupt
			state.recordType=false;
			state.recordNotFound=false;
			state.CRCError=false;
			state.lostData=false;
			state.writeFault=false;
			if(true==state.busy)
			{
				state.lastCmd=cmd;
				state.busy=false;
				state.lastStatus&=0xFE; // Bit0 must be cleared.
				return;                 // Other bits stays the same.
			}
			state.busy=false;
			state.CRCErrorAfterRead=false;
			break;
		}
	}
	state.lastCmd=cmd;
	state.lastStatus=MakeUpStatus(cmd);
}
unsigned int DiskDrive::CommandToCommandType(unsigned int cmd) const
{
	if(0xFE==cmd)
	{
		return 4;
	}
	switch(cmd&0xF0)
	{
	case 0x00: // Restore
	case 0x10: // Seek
	case 0x20: // Step?
	case 0x30: // Step?
	case 0x40: // Step In
	case 0x50: // Step In
	case 0x60: // Step Out
	case 0x70: // Step Out
		return 1;

	case 0x80: // Read Data (Read Sector)
	case 0x90: // Read Data (Read Sector)
	case 0xA0: // Write Data (Write Sector)
	case 0xB0: // Write Data (Write Sector)
		return 2;

	case 0xC0: // Read Address
	case 0xE0: // Read Track
	case 0xF0: // Write Track
		return 3;

	case 0xD0: // Force Interrupt
		return 4;
	}
	return 0; // What?
}
unsigned char DiskDrive::MakeUpStatus(unsigned int cmd) const
{
	unsigned char data=0;
	if(0xFE==cmd)
	{
		cmd=0xD0; // System ROM is using this 0xFE.  Same as 0xD0?  Or Reset?
	}
	data|=(true!=DriveReady() ? 0x80 : 0);
	data|=(true==state.busy ? 0x01 : 0);
	switch(cmd&0xF0)
	{
	case 0x00: // Restore
	case 0x10: // Seek
	case 0x20: // Step?
	case 0x30: // Step?
	case 0x40: // Step In
	case 0x50: // Step In
	case 0x60: // Step Out
	case 0x70: // Step Out
		data|=(WriteProtected() ? 0x40 : 0);
		data|=(DriveReady() ?     0x20 : 0); // Head-Engaged: Make it same as drive ready.
		data|=(SeekError() ?      0x10 : 0);
		data|=(CRCError() ?       0x08 : 0);
		data|=(state.drive[DriveSelect()].trackPos==0 ? 0x04 : 0);
		data|=(IndexHole() ?      0x02 : 0);
		break;

	case 0x80: // Read Data (Read Sector)
	case 0x90: // Read Data (Read Sector)
		data|=(RecordType() ?     0x20 : 0);
		data|=(RecordNotFound() ? 0x10 : 0);
		data|=(CRCError() ?       0x08 : 0);
		data|=(LostData() ?       0x04 : 0);
		data|=(DataRequest() ?    0x02 : 0);
		break;
	case 0xA0: // Write Data (Write Sector)
	case 0xB0: // Write Data (Write Sector)
		data|=(WriteProtected() ? 0x40 : 0);
		data|=(WriteFault() ?     0x20 : 0);
		data|=(RecordNotFound() ? 0x10 : 0);
		data|=(CRCError() ?       0x08 : 0);
		data|=(LostData() ?       0x04 : 0);
		data|=(DataRequest() ?    0x02 : 0);
		break;

	case 0xC0: // Read Address
		data|=(RecordNotFound() ? 0x10 : 0);
		data|=(CRCError() ?       0x08 : 0);
		data|=(LostData() ?       0x04 : 0);
		data|=(DataRequest() ?    0x02 : 0);
		break;
	case 0xE0: // Read Track
		data|=(LostData() ?       0x04 : 0);
		data|=(DataRequest() ?    0x02 : 0);
		break;
	case 0xF0: // Write Track
		data|=(WriteProtected() ? 0x40 : 0);
		data|=(WriteFault() ?     0x20 : 0);
		data|=(LostData() ?       0x04 : 0);
		data|=(DataRequest() ?    0x02 : 0);
		break;

	case 0xD0: // Force Interrupt
		data|=(WriteProtected() ? 0x40 : 0);
		data|=(DriveReady() ?     0x20 : 0); // Head-Engaged: Make it same as drive ready.
		data|=(state.drive[DriveSelect()].trackPos==0 ? 0x04 : 0);
		data|=(IndexHole() ?      0x02 : 0);
		data&=0xFE;
		break;
	}
	return data;
}
unsigned int DiskDrive::DriveSelect(void) const
{
	if(0!=(state.driveSelectBit&1))
	{
		return 0;
	}
	if(0!=(state.driveSelectBit&2))
	{
		return 1;
	}
	if(0!=(state.driveSelectBit&4))
	{
		return 2;
	}
	if(0!=(state.driveSelectBit&8))
	{
		return 3;
	}
	return 0;
}

unsigned int DiskDrive::GetDriveMode(void) const
{
	// Probably DDEN==0 means 2D (320K)  I'm not sure.
	// OASYS tries to write to 2HD disk with DDEN==0.
	// if(true!=state.DDEN)
	// {
	// 	return MEDIA_SINGLE_DENSITY;
	// }
	if(true==state.HISPD && true==state.MODEB)
	{
		return MEDIA_2HD_1440KB;
	}
	else if(true==state.HISPD && true!=state.MODEB)
	{
		return MEDIA_2HD_1232KB;
	}
	else if(true!=state.HISPD)
	{
		return MEDIA_2DD_640KB;
	}
	return MEDIA_UNKNOWN;
}

bool DiskDrive::DriveReady(void) const
{
	if(0!=state.driveSelectBit && nullptr!=GetDriveDisk(DriveSelect()))
	{
		if(0<state.drive[DriveSelect()].pretendDriveNotReadyCount)
		{
			--state.drive[DriveSelect()].pretendDriveNotReadyCount;
			return false;
		}
		return true;
	}
	return false;
}
bool DiskDrive::WriteProtected(void) const
{
	auto diskPtr=GetDriveDisk(DriveSelect());
	if(nullptr!=diskPtr)
	{
		return diskPtr->IsWriteProtected();
	}
	return false; // Tentative.
}
bool DiskDrive::SeekError(void) const
{
	return false;
}
bool DiskDrive::CRCError(void) const
{
	return state.CRCError;
}
bool DiskDrive::IndexHole(void) const
{
	return false;
}
bool DiskDrive::RecordType(void) const
{
	return state.recordType;
}
bool DiskDrive::RecordNotFound(void) const
{
	return state.recordNotFound;
}
bool DiskDrive::LostData(void) const
{
	return state.lostData;
}
bool DiskDrive::DataRequest(void) const
{
	return false;
}
bool DiskDrive::WriteFault(void) const
{
	return state.writeFault;
}


////////////////////////////////////////////////////////////

void DiskDrive::Reset(void)
{
	state.Reset();
}

std::vector <std::string> DiskDrive::GetStatusText(void) const
{
	std::string line;
	std::vector <std::string> text;

	text.push_back(line);
	text.back()="FDC";

	for(auto &drv : state.drive)
	{
		const int driveNum=int(&drv-state.drive);
		auto imgFilePtr=GetDriveImageFile(driveNum);

		text.push_back(line);
		text.back()="Drive"+cpputil::Ubtox(driveNum)+" ";
		if(nullptr!=imgFilePtr)
		{
			text.back()+="(";
			text.back()+=imgFilePtr->fName;
			text.back()+=")";
		}
		text.back()+="  MEDIA:";
		text.back()+=MediaTypeToString(drv.mediaType);

		text.push_back(line);
		text.back()+="TRKPOS:"+cpputil::Uitoa(drv.trackPos)+" TRKREG:"+cpputil::Uitoa(drv.trackReg);
		text.back()+=" SEC:"+cpputil::Uitoa(drv.sectorReg)+" LAST SEEK DIR:"+cpputil::Itoa(drv.lastSeekDir);
		text.back()+=" DATAREG:"+cpputil::Ubtox(drv.dataReg)+" MOTOR:"+(drv.motor ? "ON" : "OFF");
	}

	text.push_back(line);
	text.back()="DRVSELBIT:"+cpputil::Ubtox(state.driveSelectBit)+" SIDE:"+cpputil::Ubtox(state.side);

	text.push_back(line);
	text.back()="BUSY:";
	text.back()+=(state.busy ? "1" : "0");
	text.back()+=" MODEB:";
	text.back()+=(state.MODEB ? "1" : "0");
	text.back()+=" HISPD:";
	text.back()+=(state.HISPD ? "1" : "0");
	text.back()+=" INUSE:";
	text.back()+=(state.INUSE ? "1" : "0");

	text.push_back(line);
	text.back()="CLKSEL:";
	text.back()+=(state.CLKSEL ? "1" : "0");
	text.back()+=" DDEN:";
	text.back()+=(state.DDEN ? "1" : "0");
	text.back()+=" IRQMSK:";
	text.back()+=(state.IRQMSK ? "1" : "0");

	text.push_back("DRIVE MODE:");
	text.back()+=MediaTypeToString(GetDriveMode());

	text.push_back(line);
	text.back()="RecordType:";
	text.back()+=(state.recordType ? "1" : "0");
	text.back()+=" RecNotFound:";
	text.back()+=(state.recordNotFound ? "1" : "0");
	text.back()+=" CRCError:";
	text.back()+=(state.CRCError ? "1" : "0");
	text.back()+=" LostData:";
	text.back()+=(state.lostData ? "1" : "0");

	text.push_back(line);
	text.back()="Last CMD:";
	text.back()+=cpputil::Ubtox(state.lastCmd);
	text.back()+=" ";
	text.back()+=FDCCommandToExplanation(state.lastCmd);
	text.back()+=" STATUS:";
	text.back()+=cpputil::Ubtox(state.lastStatus);

	return text;
}

/* static */ std::string DiskDrive::FDCCommandToExplanation(unsigned char cmd)
{
	std::string str;
	switch(cmd&0xF0)
	{
	case 0x00: // Restore
		str="Restore";
		break;
	case 0x10: // Seek
		str="Seek";
		break;
	case 0x20: // Step?
	case 0x30: // Step?
		str="Step";
		break;
	case 0x40: // Step In
	case 0x50: // Step In
		str="Step_In";
		break;
	case 0x60: // Step Out
	case 0x70: // Step Out
		str="Step_Out";
		break;

	case 0x80: // Read Data (Read Sector)
	case 0x90: // Read Data (Read Sector)
		str="Read_Sector";
		break;
	case 0xA0: // Write Data (Write Sector)
	case 0xB0: // Write Data (Write Sector)
		str="Write_Sector";
		break;

	case 0xC0: // Read Address
		str="Read_Address";
		break;
	case 0xE0: // Read Track
		str="Read_Track";
		break;
	case 0xF0: // Write Track
		str="Write_Track";
		break;

	default:
	case 0xD0: // Force Interrupt
		str="Force_Interrupt";
		break;
	}
	return str;
}

/* static */ std::string DiskDrive::MediaTypeToString(unsigned int mediaType)
{
	switch(mediaType)
	{
	default:
	case MEDIA_UNKNOWN:
		return "Unknown/Empty";
	case MEDIA_2D:
		return "2D";
	case MEDIA_2DD_640KB:
		return "2DD 640KB";
	case MEDIA_2DD_720KB:
		return "2DD 720KB";
	case MEDIA_2HD_1232KB:
		return "2HD 1232KB";
	case MEDIA_2HD_1440KB:
		return "2DD 1440KB";
	case MEDIA_SINGLE_DENSITY:
		return "1DD?";
	}
}

/* virtual */ uint32_t DiskDrive::SerializeVersion(void) const
{
	// Version 2 adds fields for I/O read/write (not DMA)
	// Version 3 adds CRCErrorAfterRead
	return 3;
}
/* virtual */ void DiskDrive::SpecificSerialize(std::vector <unsigned char> &data,std::string stateFName) const
{
	std::string stateDir,stateName;
	cpputil::SeparatePathFile(stateDir,stateName,stateFName);

	PushUint32(data,NUM_DRIVES);
	for(auto &imgf : imgFile)
	{
		std::string fName;
		std::vector <unsigned char> dskImg;
		if(0<imgf.d77.GetNumDisk())
		{
			PushUint32(data,imgf.fileType);
			PushString(data,imgf.fName);  // As is
			PushString(data,cpputil::MakeRelativePath(imgf.fName,stateDir)); // Relpath
			PushUcharArray(data,imgf.d77.MakeD77Image());
		}
		else
		{
			PushUint32(data,imgf.fileType);
			PushString(data,""); // As is
			PushString(data,""); // Relpath
			PushUcharArray(data,dskImg);
		}
	}

	for(auto &drv : state.drive)
	{
		PushInt32(data,drv.trackPos);      // Actual head location.
		PushInt32(data,drv.trackReg);      // Value in track register 0202H
		PushInt32(data,drv.sectorReg);     // Value in sector register 0x04H
		PushInt32(data,drv.dataReg);       // Value in data register 0x06H

		PushInt32(data,drv.lastSeekDir);   // For STEP command.
		PushInt32(data,drv.imgFileNum);    // Pointer to imgFile.
		PushInt32(data,drv.diskIndex);     // Disk Index in imgFile[imgFileNum]
		PushInt32(data,drv.mediaType);

		PushBool(data,drv.motor);
		PushBool(data,drv.diskChange);
		PushInt32(data,drv.pretendDriveNotReadyCount);
	}

	PushBool(data,state.driveSwitch);  // [2] pp.258
	PushBool(data,state.busy);
	PushBool(data,state.MODEB);  // [2] pp.258, pp.809
	PushBool(data,state.HISPD);  // [2] pp.258, pp.809
	PushBool(data,state.INUSE);
	PushUint32(data,state.side); // Is side common for all drives?  Or Per drive?
	PushBool(data,state.CLKSEL);
	PushBool(data,state.DDEN);
	PushBool(data,state.IRQMSK);

	PushUint32(data,state.driveSelectBit);
	PushUint32(data,state.lastCmd);
	PushUint32(data,state.lastStatus);

	PushBool(data,state.recordType);
	PushBool(data,state.recordNotFound);
	PushBool(data,state.CRCError);
	PushBool(data,state.lostData);
	PushBool(data,state.writeFault);
	PushUint32(data,state.addrMarkReadCount);

	PushInt64(data,state.scheduleTime);

	// Version 2
	PushUint32(data,state.dataReadPointer);
	PushUint32(data,state.expectedWriteLength);
	PushUcharArray(data,data);
	PushBool(data,state.DRQ);
	PushBool(data,state.IRQ);
	// Version 3
	PushBool(data,state.CRCErrorAfterRead);
}
/* virtual */ bool DiskDrive::SpecificDeserialize(const unsigned char *&data,std::string stateFName,uint32_t version)
{
	std::string stateDir,stateName;
	cpputil::SeparatePathFile(stateDir,stateName,stateFName);

	ReadUint32(data); // Dummy read NUM_DRIVES
	for(auto &imgf : imgFile)
	{
		imgf.fileType=ReadUint32(data);
		auto fName=ReadString(data);
		std::string relPath;
		if(1<=version)
		{
			relPath=ReadString(data);
		}
		auto dskImg=ReadUcharArray(data);

		if(""!=fName)
		{
			// See disk-image search rule in townsstate.cpp
			bool loaded=false;

			// (1) Try using the filename stored in the state file as is.
			if(true!=loaded)
			{
				loaded=imgf.LoadD77orRAW(fName);
			}

			// (2) Try state path+relative path
			auto stateRel=cpputil::MakeFullPathName(stateDir,relPath);
			if(true!=loaded)
			{
				loaded=imgf.LoadD77orRAW(stateRel);
			}

			// (3) Try image search path+file name
			if(true!=loaded)
			{
				std::string imgDir,imgName;
				cpputil::SeparatePathFile(imgDir,imgName,fName);
				for(auto path : searchPaths)
				{
					auto ful=cpputil::MakeFullPathName(path,imgName);
					loaded=imgf.LoadD77orRAW(ful);
					if(true==loaded)
					{
						break;
					}
				}
			}

			// (4) Try state path+file name
			if(true!=loaded)
			{
				std::string imgDir,imgName;
				cpputil::SeparatePathFile(imgDir,imgName,fName);
				auto ful=cpputil::MakeFullPathName(stateDir,imgName);
				loaded=imgf.LoadD77orRAW(ful);
			}

			// (5) If floppy-disk image, use image stored in the state file.
			if(true!=loaded && 0<dskImg.size())
			{
				if(cpputil::IsRelativePath(fName))
				{
					fName=cpputil::MakeFullPathName(stateDir,fName);
				}
				imgf.fName=fName;
				imgf.d77.SetData(dskImg,false);
			}
		}
	}

	for(auto &drv : state.drive)
	{
		drv.trackPos=ReadInt32(data);      // Actual head location.
		drv.trackReg=ReadInt32(data);      // Value in track register 0202H
		drv.sectorReg=ReadInt32(data);     // Value in sector register 0x04H
		drv.dataReg=ReadInt32(data);       // Value in data register 0x06H

		drv.lastSeekDir=ReadInt32(data);   // For STEP command.
		drv.imgFileNum=ReadInt32(data);    // Pointer to imgFile.
		drv.diskIndex=ReadInt32(data);     // Disk Index in imgFile[imgFileNum]
		drv.mediaType=ReadInt32(data);

		drv.motor=ReadBool(data);
		drv.diskChange=ReadBool(data);
		drv.pretendDriveNotReadyCount=ReadInt32(data);
	}

	state.driveSwitch=ReadBool(data);  // [2] pp.258
	state.busy=ReadBool(data);
	state.MODEB=ReadBool(data);  // [2] pp.258, pp.809
	state.HISPD=ReadBool(data);  // [2] pp.258, pp.809
	state.INUSE=ReadBool(data);
	state.side=ReadUint32(data); // Is side common for all drives?  Or Per drive?
	state.CLKSEL=ReadBool(data);
	state.DDEN=ReadBool(data);
	state.IRQMSK=ReadBool(data);

	state.driveSelectBit=ReadUint32(data);
	state.lastCmd=ReadUint32(data);
	state.lastStatus=ReadUint32(data);

	state.recordType=ReadBool(data);
	state.recordNotFound=ReadBool(data);
	state.CRCError=ReadBool(data);
	state.lostData=ReadBool(data);
	state.writeFault=ReadBool(data);
	state.addrMarkReadCount=ReadUint32(data);

	state.scheduleTime=ReadInt64(data);

	if(2<=version)
	{
		state.dataReadPointer=ReadUint32(data);
		state.expectedWriteLength=ReadUint32(data);
		state.data=ReadUcharArray(data);
		state.DRQ=ReadBool(data);
		state.IRQ=ReadBool(data);
	}
	if(3<=version)
	{
		state.CRCErrorAfterRead=ReadBool(data);
	}
	return true;
}
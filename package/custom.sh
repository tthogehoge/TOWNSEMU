/sbin/ifconfig p2p0 down
echo >> /etc/network/interfaces
echo "iface p2p0 inet manual" >> /etc/network/interfaces
echo "  up ifconfig p2p0 down" >> /etc/network/interfaces
echo "  down ifconfig p2p0 down" >> /etc/network/interfaces

tar xf /userdata/system/fmtowns.tar -C /


#!/bin/bash
yum install -y net-tools nedit */libGL.so.1 */libGLU.so.1
echo ""
echo "  ...done. Customizing docker..."
echo ""
echo "  Licensing for:" `hostname`
cp /opt/local/Amira-5.5.0/share/license/password.dat /opt/local/Amira-5.5.0/share/license/password.dat.bkup
cp /opt/local/Amira-5.5.0/share/license/FLEXnet/passwordServer.dat /opt/local/Amira-5.5.0/share/license/FLEXnet/passwordServer.dat.bkup
sed -i "s/sbterm05/`hostname`/g" /opt/local/Amira-5.5.0/share/license/password.dat
sed -i "s/sbterm05/`hostname`/g" /opt/local/Amira-5.5.0/share/license/FLEXnet/passwordServer.dat 

echo "  ...done. Starting license server..."
/extra/start-amira-license.sh
echo "  ...done. All ready to launch."
/extra/start-amira.sh
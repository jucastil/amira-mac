#!/bin/sh
# Shell script to install Services
 

if [ `id -u` -ne 0 ]
then
    echo "Error: must be root."
    exit -2
fi


exit_usage() {
    echo "Error: wrong usage (as root only) :"
    echo " - sh serviceSetup.sh install   <service_name> <service_description> <service_path> <run_as_user>"
    echo " - sh serviceSetup.sh uninstall <service_name>"
    echo " - sh serviceSetup.sh start     <service_name>"
    echo " - sh serviceSetup.sh stop      <service_name>"
    echo " - sh serviceSetup.sh status    <service_name>"
    exit -1
}

case $1 in

    'install')
        [ $# -eq 5 ] || exit_usage

        echo -e "#!/bin/sh"\
              "\n# description: $3"\
              "\n# chkconfig: 5 99 0"\
              "\n"\
              "\n#source function library"\
              "\n. /etc/init.d/functions"\
              "\n"\
              "\ncase "'$1'" in"\
              "\n    'start')"\
              "\n        [ -f /var/lock/subsys/$2 ] && exit 0"\
              "\n# append \"-asservice\" to notify the app that it runs as a daemon, not in console mode"\
              "\n        daemon --user $5 $4 -asservice"\
              "\n        touch /var/lock/subsys/$2"\
              "\n        echo Starting $2..."\
              "\n    ;;"\
              "\n    'stop')"\
              "\n        killproc $2"\
              "\n        rm -f /var/lock/subsys/$2"\
              "\n        echo Stopping $2..."\
              "\n    ;;"\
              "\n    'restart')"\
              "\n        "'$0'" stop"\
              "\n        "'$0'" start"\
              "\n    ;;"\
              "\n    'status')"\
              "\n        status $2"\
              "\n        exit "'$?'\
              "\n    ;;"\
              "\n    *)"\
              "\n        echo \"Usage : $2 {start|stop|restart|status}\""\
              "\n        exit -1"\
              "\n    ;;"\
              "\nesac"\
              "\nexit 0"\
              "\n" > /etc/init.d/$2

        chmod +x /etc/init.d/$2

        ln -sf /etc/init.d/$2 /etc/rc0.d/K00$2
        ln -sf /etc/init.d/$2 /etc/rc1.d/K00$2
        ln -sf /etc/init.d/$2 /etc/rc2.d/K00$2
        ln -sf /etc/init.d/$2 /etc/rc3.d/K00$2
        ln -sf /etc/init.d/$2 /etc/rc4.d/K00$2
        ln -sf /etc/init.d/$2 /etc/rc5.d/S99$2
        ln -sf /etc/init.d/$2 /etc/rc6.d/K00$2
 
        echo "$2 installed."
        exit 0
        ;;

    'uninstall')
        [ $# -eq 2 ] || exit_usage

        sh $0 stop $2
        if [ $? -ne 0 ]
        then
            echo "$2 uninstall failed."
            exit -1
        fi
        
        rm -f /etc/init.d/$2
        
        rm -f /etc/rc0.d/K00$2
        rm -f /etc/rc1.d/K00$2
        rm -f /etc/rc2.d/K00$2
        rm -f /etc/rc3.d/K00$2
        rm -f /etc/rc4.d/K00$2
        rm -f /etc/rc5.d/S99$2
        rm -f /etc/rc6.d/K00$2

        echo "$2 uninstalled."
        exit 0
        ;;

    'start')
        [ $# -eq 2 ] || exit_usage
    
        if [ ! -f /etc/init.d/$2 ] 
        then 
            echo Error: $2 not installed
            exit -1
        fi
        
        /etc/init.d/$2 start
                
        /etc/init.d/$2 status >& /dev/null
        if [ $? -ne 0 ]
        then
            echo "$2 start failed."
            exit -1
        fi

        echo "$2 started."
        exit 0
        ;;

    'stop')
        [ $# -eq 2 ] || exit_usage

        if [ ! -f /etc/init.d/$2 ]
        then
            echo Error: $2 not installed
            exit -1
        fi

        /etc/init.d/$2 stop
        
        /etc/init.d/$2 status >& /dev/null   
        if [ $? -ne 3 ]
        then
            echo "$2 stop failed."
            exit -1
        fi

        echo "$2 stopped."
        exit 0
        ;;

    'status')
        [ $# -eq 2 ] || exit_usage

        if [ ! -f /etc/init.d/$2 ]
        then
            echo "$2 not installed."
            exit 0
        else
            /etc/init.d/$2 status >& /dev/null
            case $? in
            0)
                echo "$2 installed and running."
	        exit 11
                ;;
            *)
                echo "$2 installed but stopped."
	        exit 1
                ;;
            esac
        fi
	;;

    *)
        exit_usage
        ;;
        
esac


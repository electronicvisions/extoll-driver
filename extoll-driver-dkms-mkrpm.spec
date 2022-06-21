%{?!module_name: %{error: You did not specify a module name (%%module_name)}}
%{?!version: %{error: You did not specify a module version (%%version)}}
%{?!kernel_versions: %{error: You did not specify kernel versions (%%kernel_version)}}
%{?!packager: %define packager DKMS <dkms-devel@lists.us.dell.com>}
%{?!license: %define license Unknown}
%{?!_dkmsdir: %define _dkmsdir /var/lib/dkms}
%{?!_srcdir: %define _srcdir %_prefix/src}
%{?!_datarootdir: %define _datarootdir %{_datadir}}

%define extoll_include /opt/extoll/x86_64/include
%define build_timestamp %(date +"%s")

Summary:	%{module_name} %{version} dkms package
Name:		%{module_name}
Version:	%{version}
License:	%license
Release:	0.%{build_timestamp}
#Release:	1
BuildArch:	noarch
Group:		System/Kernel
Requires: 	dkms >= 1.95 extoll-support extoll-kernel-headers
BuildRequires: 	dkms
BuildRoot: 	%{_tmppath}/%{name}-%{version}-%{release}-root/

%description
Kernel modules for %{module_name} %{version} in a DKMS wrapper.
Installs headers to %extoll_include

%prep
if [ "%mktarball_line" != "none" ]; then
        /usr/sbin/dkms mktarball -m %module_name -v %version %mktarball_line --archive `basename %{module_name}-%{version}.dkms.tar.gz`
        cp -af %{_dkmsdir}/%{module_name}/%{version}/tarball/`basename %{module_name}-%{version}.dkms.tar.gz` %{module_name}-%{version}.dkms.tar.gz
fi

%install
if [ "$RPM_BUILD_ROOT" != "/" ]; then
        rm -rf $RPM_BUILD_ROOT
fi
mkdir -p $RPM_BUILD_ROOT/%{_srcdir}
mkdir -p $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}

if [ -d %{_sourcedir}/%{module_name}-%{version} ]; then
        cp -Lpr %{_sourcedir}/%{module_name}-%{version} $RPM_BUILD_ROOT/%{_srcdir}
fi

if [ -f %{module_name}-%{version}.dkms.tar.gz ]; then
        install -m 644 %{module_name}-%{version}.dkms.tar.gz $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}
fi

if [ -f %{_sourcedir}/common.postinst ]; then
        install -m 755 %{_sourcedir}/common.postinst $RPM_BUILD_ROOT/%{_datarootdir}/%{module_name}/postinst
fi

#mkdir -p $RPM_BUILD_ROOT/%{extoll_include}
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/velo2_mod.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/velo2_ioctl.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/rma2_region.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/arch_define.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/rma2drv.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/rma2_ioctl.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/pmap.h $RPM_BUILD_ROOT/%extoll_include
#install -m 644 %{_sourcedir}/%{module_name}-%{version}/extoll_rf_access_ioctl.h $RPM_BUILD_ROOT/%extoll_include

mkdir -p $RPM_BUILD_ROOT/usr/lib/dracut/dracut.conf.d/
install -m 644 %{_sourcedir}/%{module_name}-%{version}/dracut.conf $RPM_BUILD_ROOT/usr/lib/dracut/dracut.conf.d/60-extoll.conf

%clean
if [ "$RPM_BUILD_ROOT" != "/" ]; then
        rm -rf $RPM_BUILD_ROOT
fi

%pre
echo "Stopping master"
systemctl stop emp-daemon 2> /dev/null
echo "Stopping slave"
systemctl stop emp-slave-daemon 2> /dev/null
echo "Unloading EXTOLL kernel modules."
rmmod exn 2> /dev/null
rmmod extoll_rf_access 2> /dev/null
rmmod extoll_kapi 2> /dev/null
rmmod velo2 2> /dev/null
rmmod rma2 2> /dev/null
rmmod extoll_bq 2> /dev/null
rmmod atu2 2> /dev/null
rmmod smfu2 2> /dev/null
rmmod pmap 2> /dev/null
rmmod extoll 2> /dev/null
rmmod extoll_rf_sysfs 2> /dev/null
exit 0

%post
#-- old stuff
#for POSTINST in %{_prefix}/lib/dkms/common.postinst %{_datarootdir}/%{module_name}/postinst; do
#        if [ -f $POSTINST ]; then
#                $POSTINST %{module_name} %{version} %{_datarootdir}/%{module_name}
#                exit $?
#        fi
#        echo "WARNING: $POSTINST does not exist."
#done
#echo -e "ERROR: DKMS version is too old and %{module_name} was not"
#echo -e "built with legacy DKMS support."
#echo -e "You must either rebuild %{module_name} with legacy postinst"
#echo -e "support or upgrade DKMS to a more current version."
#exit 1
for POSTINST in %{_prefix}/lib/dkms/common.postinst %{_datarootdir}/%{module_name}/postinst; do
        if [ -f $POSTINST ]; then
                $POSTINST %{module_name} %{version} %{_datarootdir}/%{module_name}
                RET=$?
                if [ $RET -gt 0 ] ; then
                      exit $RET
                fi
                echo "Loading EXTOLL kernel modules."
                modprobe exn 2> /dev/null
                modprobe extoll_rf_access 2> /dev/null
                modprobe extoll_kapi 2> /dev/null
                modprobe velo2 2> /dev/null
                modprobe rma2 2> /dev/null
                modprobe extoll_bq 2> /dev/null
                modprobe atu2 2> /dev/null
                modprobe smfu2 2> /dev/null
                modprobe pmap 2> /dev/null
                modprobe extoll 2> /dev/null
                modprobe extoll_rf_sysfs 2> /dev/null
                exit 0
        fi
        echo "WARNING: $POSTINST does not exist."
done
exit 1


%preun
# $1 == 1 on update
# $1 == 0 on remove
if [ $1 -eq 0 ] ; then
  echo -e
  echo -e "Uninstall of %{module_name} module (version %{version}) beginning:"
  dkms remove -m %{module_name} -v %{version} --all --rpm_safe_upgrade
fi
exit 0

%files
%defattr(-,root,root)
%{_srcdir}
%{_datarootdir}/%{module_name}/
#%{extoll_include}/velo2_mod.h
#%{extoll_include}/velo2_ioctl.h
#%{extoll_include}/rma2_region.h
#%{extoll_include}/arch_define.h
#%{extoll_include}/rma2drv.h
#%{extoll_include}/rma2_ioctl.h
#%{extoll_include}/pmap.h
#%{extoll_include}/extoll_rf_access_ioctl.h
%config /usr/lib/dracut/dracut.conf.d/60-extoll.conf

%changelog
* %(date "+%a %b %d %Y") %packager %{version}-%{release}
- Automatic build by DKMS


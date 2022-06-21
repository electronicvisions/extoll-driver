###############################################################################
#EXTOLL DEFINES
###############################################################################
%define extoll_root /opt/extoll/x86_64
%define extoll_bin %extoll_root/bin
%define extoll_lib %extoll_root/lib
%define extoll_include %extoll_root/include
%define build_timestamp %(date +"%s")

Name:           extoll-kernel-headers
Version:	%{version}
Release:	0.%{build_timestamp}
#Release:	1
BuildArch:	noarch

Summary:        EXTOLL kernel headers

License:        LGPL v3.0
URL:            http://www.extoll.de
Source0:        extoll-kernel-headers.tar.gz

%description
Support Package for the EXTOLL Software Distribution.

%prep
%setup -q -c

%install
if [ "$RPM_BUILD_ROOT" != "/" ]; then
        rm -rf $RPM_BUILD_ROOT
fi
mkdir -p $RPM_BUILD_ROOT/%{extoll_include}

install -m 644 velo2_mod.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 velo2_ioctl.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 rma2_region.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 arch_define.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 rma2drv.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 rma2_ioctl.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 pmap.h $RPM_BUILD_ROOT/%extoll_include
install -m 644 extoll_rf_access_ioctl.h $RPM_BUILD_ROOT/%extoll_include


%files
%{extoll_include}/velo2_mod.h
%{extoll_include}/velo2_ioctl.h
%{extoll_include}/rma2_region.h
%{extoll_include}/arch_define.h
%{extoll_include}/rma2drv.h
%{extoll_include}/rma2_ioctl.h
%{extoll_include}/pmap.h
%{extoll_include}/extoll_rf_access_ioctl.h

%changelog

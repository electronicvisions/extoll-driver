#!/bin/sh

#PACKAGE_NAME=`sed -n '/PACKAGE_NAME/p' dkms.conf | sed -e 's/PACKAGE_NAME=//'`
PACKAGE_VERSION=`sed -n '/PACKAGE_VERSION/p' dkms.conf | sed -e 's/PACKAGE_VERSION=//'`

rpmdev-setuptree
cp extoll-kernel-headers.spec ~/rpmbuild/SPECS/
tar caf ~/rpmbuild/SOURCES/extoll-kernel-headers.tar.gz *.h
rpmbuild -bb -D "version ${PACKAGE_VERSION}" ~/rpmbuild/SPECS/extoll-kernel-headers.spec
cp ~/rpmbuild/RPMS/noarch/extoll-kernel-headers-*.rpm .

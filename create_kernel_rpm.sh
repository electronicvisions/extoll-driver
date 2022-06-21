#!/bin/sh

PACKAGE_NAME=`sed -n '/PACKAGE_NAME/p' dkms.conf | sed -e 's/PACKAGE_NAME=//'`
PACKAGE_VERSION=`sed -n '/PACKAGE_VERSION/p' dkms.conf | sed -e 's/PACKAGE_VERSION=//'`
MODULE_FOLDER=/usr/src/$PACKAGE_NAME-$PACKAGE_VERSION
mkdir -p $MODULE_FOLDER
cp -R * $MODULE_FOLDER
dkms add -m $PACKAGE_NAME -v $PACKAGE_VERSION || exit 1
dkms mkrpm --source-only -m $PACKAGE_NAME -v $PACKAGE_VERSION || exit 1
cp /var/lib/dkms/$PACKAGE_NAME/$PACKAGE_VERSION/rpm/*.noarch.rpm .


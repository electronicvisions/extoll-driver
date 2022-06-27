def depends(dep):
    pass


def options(opt):
    pass


def configure(cfg):
    pass


def build(bld):
    bld(target          = 'extoll-driver_inc',
        export_includes = '.'
    )

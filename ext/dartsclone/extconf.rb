require 'mkmf'

$INCFLAGS << " -I$(srcdir)/src"
$VPATH << "$(srcdir)/src"

create_makefile('dartsclone/dartscloneext')

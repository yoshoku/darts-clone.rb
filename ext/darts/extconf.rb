require 'mkmf'

abort 'libstdc++ is not found.' unless have_library('stdc++')

$INCFLAGS << " -I$(srcdir)/src"
$VPATH << "$(srcdir)/src"

create_makefile('darts/dartsext')

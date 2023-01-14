* † -> Š‘

set safe off
*set console on
set console off
clear

close data

************


sele 1
*use  rj_
use  mdmf_j

sele 2
*use  ks_
use  mdmf_k
zap


sele mdmf_j
goto top

LOCATE  for .T.

**

do while .T.

  if eof()
	exit
  endif

do recxx

sele mdmf_j
skip

enddo

**

close data
***********

clear


return
**************************************************
**************************************************
proc recxx

sele mdmf_j
scat memvar 

sele mdmf_k

**

append blank

repl mdmf_kdata   with m.mdmf_jdata
repl mdmf_kdokk   with m.mdmf_jdokk
repl mdmf_kdokn   with m.mdmf_jdokn
repl mdmf_kdokd   with m.mdmf_jdokd
repl mdmf_kto    with m.mdmf_jto

repl mdmf_ks     with m.mdmf_jdb
repl mdmf_ksn    with m.mdmf_jdbn
repl mdmf_kks    with m.mdmf_jkr
repl mdmf_kksn   with m.mdmf_jkrn

repl mdmf_kdb   with m.mdmf_jrub
repl mdmf_kkr   with 0

******
append blank

repl mdmf_kdata   with m.mdmf_jdata
repl mdmf_kdokk   with m.mdmf_jdokk
repl mdmf_kdokn   with m.mdmf_jdokn
repl mdmf_kdokd   with m.mdmf_jdokd
repl mdmf_kto     with m.mdmf_jto


repl mdmf_ks     with m.mdmf_jkr
repl mdmf_ksn    with m.mdmf_jkrn
repl mdmf_kks    with m.mdmf_jdb
repl mdmf_kksn   with m.mdmf_jdbn

repl mdmf_kkr   with m.mdmf_jrub

repl mdmf_kdb   with 0


return
***************************
***************************

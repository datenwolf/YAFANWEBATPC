#!/bin/bash
if [ "_$1" = "_-get" ]
then l=$(basename $2); l=${l//.png/} ; l=${l//"_"/"="} ; echo $l | base64 -d
exit
fi
set -v
qm_main="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug"

qm_list="CONFIG+=qtToTextureFlip CONFIG+=textureflip"
qm_list_count=2

qm_for="$(seq 1 $qm_list_count)"
if [ "_$1" = "_-nested" ]
    then echo 'qm_main="'$qm_main'"' > testsuite.tmp
    echo 'qm_list="'$qm_list'"' >> testsuite.tmp
    for i in $qm_for
        do echo 'for cfg'$i' in "" $qm_list ; do qm_list=${qm_list//"$cfg'$i'"/}' >> testsuite.tmp
    done
cat >>testsuite.tmp <<END
[ -f Makefile ] && make distclean
END
    echo 'tmp="$qm_main'$(for i in $qm_for ; do echo -n ' $cfg'$i ;done)'"' >> testsuite.tmp
cat >>testsuite.tmp <<END
cfg=\$(echo "\$tmp" | base64 -w 0 | tr "=" "_")
\$tmp
make > \$cfg.make.stdout 2> \$cfg.make.stderr
./yafanwebatpc > \$cfg.stdout 2> \$cfg.stderr &
sleep 20
import -window root \$cfg.png
killall yafanwebatpc
sleep 2
killall -9 yafanwebatpc
END
for i in $qm_for ; do echo 'done' ;done >> testsuite.tmp
bash -v testsuite.tmp
else
    git pull
    $0 -nested 2>&1 | tee suite.stdouterr
fi
set +v

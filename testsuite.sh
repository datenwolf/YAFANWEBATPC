#!/bin/bash -v

qm_dbgtexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=textureflip"
qm_dbgnotexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug"
qm_reltexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=release CONFIG+=textureflip"
qm_relnotexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=release"

if [ "_$1" = "_-nested" ]
    then for cfg in dbgtexflip dbgnotexflip reltexflip relnotexflip
        do make distclean
        eval "tmp=\$qm_${cfg}"
        $tmp
        make > $cfg.make.stdout 2> $cfg.make.stderr
        ./yafanwebatpc > $cfg.stdout 2> $cfg.stderr &
        sleep 20
        import -window root $cfg.png
        killall yafanwebatpc
        sleep 2
        killall -9 yafanwebatpc
    done
else
    git pull
    $0 -nested > suite.stdout 2> suite.stderr
fi

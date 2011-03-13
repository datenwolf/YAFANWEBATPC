#!/bin/bash -v

qm_dbgtexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=textureflip"
qm_dbgnotexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug"
qm_dbgtfqf="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=textureflip CONFIG+=qtToTextureFlip"
qm_dbgtfnqf="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=qtToTextureFlip"

if [ "_$1" = "_-nested" ]
    then for cfg in dbgtexflip dbgnotexflip dbgtfqf dbgntfqf
        do [ -f Makefile ] && make distclean
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
    $0 -nested 2>&1 | tee suite.stdouterr
fi

#!/bin/bash -v

qm_dbgtexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=textureflip"
qm_dbgnotexflip="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug"
qm_dbgtfqf="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=textureflip CONFIG+=qtToTextureFlip"
qm_dbgntfqf="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++ CONFIG+=debug CONFIG+=qtToTextureFlip"

qm_main="qmake-qt4 yafanwebatpc.pro -r -spec linux-g++"

qm_list="CONFIG+=debug CONFIG+=qtToTextureFlip CONFIG+=textureflip"


if [ "_$1" = "_-nested" ]
    then for cfg1 in "" $qm_list ; do for cfg2 in "" ${qm_list//"$cfg1"/} ; do for cfg3 in "" ${{qm_list//"$cfg1"/}//"$cfg2"/} ; do
        [ -f Makefile ] && make distclean
        tmp="$qm_main $cfg1 $cfg2 $cfg3"
        cfg=$(echo "$tmp" | base64 -w 0 | tr "=" "_")
        $tmp
        make > $cfg.make.stdout 2> $cfg.make.stderr
        ./yafanwebatpc > $cfg.stdout 2> $cfg.stderr &
        sleep 20
        import -window root $cfg.png
        killall yafanwebatpc
        sleep 2
        killall -9 yafanwebatpc
    done;done;done
else
    git pull
    $0 -nested 2>&1 | tee suite.stdouterr
fi

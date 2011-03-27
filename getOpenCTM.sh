#!/bin/sh
git submodule init
git submodule update
cd openctm
make -f Makefile.linux openctm
cd ..
qmake-qt4 "LIBS += -Lopenctm/lib/" "INCLUDEPATH += openctm/lib/"
make
cat > start.sh <<EOF
#!/bin/sh
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:openctm/lib/ ./yafanwebatpc
EOF
chmod +x start.sh
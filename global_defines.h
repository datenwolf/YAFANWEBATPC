#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define ENCAPS(txt) (char*)txt.toUtf8().data()
#define I2F(i) (float)((float)i/100000.0f)
#define F2I(f) (int)(f*100000.0f)


#endif // GLOBAL_DEFINES_H

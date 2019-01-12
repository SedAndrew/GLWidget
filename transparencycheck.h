#ifndef TRANSPARENCYCHECK_H
#define TRANSPARENCYCHECK_H

struct Transparency {
    bool flag = false;

    void setEnabled(){
        flag = (true) ? false : true;
    }

    const bool &getInfo() const
    {
        return flag;
    }
};

#endif // TRANSPARENCYCHECK_H

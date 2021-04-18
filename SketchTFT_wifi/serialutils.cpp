#include "serialutils.h"

#include <Arduino.h>

bool strfind(String &str, String &tofind){
    for(int i=0;i<str.length();i++){
        if(str[i] == tofind[0] && str.length() - (i+1) >= tofind.length()){
            if(str.substring(i, tofind.length() + i) == tofind) return true;
        }
    }

    return false;
}

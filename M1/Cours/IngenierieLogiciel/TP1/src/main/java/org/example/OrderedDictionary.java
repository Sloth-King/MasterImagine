package org.example;

import java.util.Dictionary;

public class OrderedDictionary extends AbstractDictionary{

    public OrderedDictionary() {
        this.keys = new Object[0];
        this.values = new Object[0];
    }

    public int indexOf(Object key) {
        for(int i=0;i<keys.length;i++) {
            if(keys[i].equals(key)) {
                return i;
            }
        }
        return -1;
    }
    @Override
    public int newIndexOf(Object key) {
        Object[] newKeyDic = new Object[keys.length + 1];
        Object[] newValueDic = new Object[values.length + 1];
        for (int i = 0; i < keys.length; i++) {
        newKeyDic[i] = keys[i];
        newValueDic[i] = values[i];
        }
        this.keys = newKeyDic;
        this.values = newValueDic;

        return keys.length-1;
    }

}

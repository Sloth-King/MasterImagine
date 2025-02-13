package org.example;

import java.lang.reflect.Array;
import java.util.Dictionary;

public abstract class AbstractDictionary implements IDictionary {
    Object keys[] = new Object[0];
    Object values[] = new Object[0];

    @Override
    public Object get(Object key) {
        int index = indexOf(key);
        if (index == -1) {
            return null;
        }
        return values[index];
    }

    @Override
    public IDictionary put(Object key , Object value){
        if(!containsKey(key)) {
            int index = newIndexOf(key);
            keys[index] = key;
            values[index] = value;
        } else if (containsKey(key)) {
            values[indexOf(key)] = value;
        }
        return this;
    }

     @Override
    public int size(){
        return keys.length;
    }

    @Override
    public boolean IsEmpty(){
        return keys.length == 0;
    }

    @Override
    public boolean containsKey(Object key){
        for(int i = 0 ; i < keys.length ; i++ ){
            if(keys[i].equals(key)){
                return true;
            }
        }
        return false;
    }

    abstract int indexOf(Object key);
    abstract int newIndexOf(Object key);

}

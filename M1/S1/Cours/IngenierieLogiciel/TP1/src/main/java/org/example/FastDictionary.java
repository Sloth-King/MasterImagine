package org.example;

public class FastDictionary extends AbstractDictionary {

    public FastDictionary() {
        this.keys = new Object[4];
        this.values = new Object[4];
    }

    @Override
    public int indexOf(Object key) {
        int hash = key.hashCode();
        int index = hash % keys.length;

        while(keys[index] != null && !keys[index].equals(hash)){
            index = (index + 1);
        }
        return keys[index] != null ? index : -1;
    }

    public int newIndexOf(Object key) {
        if(mustGrow()){
            grow();
        }
        int hash = key.hashCode();
        int index = hash % keys.length;
        while(keys[index] != null){
            index = (index + 1);
        }
        return index;
    }

    public void grow(){
        Object[] oldKeys = keys;
        Object[] oldValues = values;
        int newCapacity = oldKeys.length + oldValues.length;

        keys = new Object[newCapacity];
        values = new Object[newCapacity];

        for(int i = 0; i < oldKeys.length; i++){
            if(oldKeys[i] != null){
                Object key = oldKeys[i];
                Object value = oldValues[i];
                int newIndex = key.hashCode() % newCapacity;

                while(keys[newIndex] != null){
                    newIndex = (newIndex + 1) % newCapacity;
                }
                keys[newIndex] = key;
                values[newIndex] = value;
            }
        }
    }

    public boolean mustGrow(){
        return size() >= keys.length * 0.75;
    }

    @Override
    public int size(){
        int sizeR = 0;
        for(int i = 0 ; i < keys.length ; i++){
            if(values[i] != null) {
                sizeR++;
            }
        }
        return sizeR;
    }


}

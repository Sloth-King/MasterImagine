package org.example;

public interface IDictionary {

    Object get(Object key);
    IDictionary put(Object key, Object value);
    boolean IsEmpty();
    int size();
    boolean containsKey(Object key);

}

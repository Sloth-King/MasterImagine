package org.example;

public class Main {
    public static void main(String[] args) {
    IDictionary dic = new OrderedDictionary();
    System.out.println("Size : " + dic.size());
    System.out.println("Is Empty : " + dic.IsEmpty());
    dic.put(0, 0);
    System.out.println("Put value : ('hello' , 'world')" );
    System.out.println("Get : " + dic.get(0));
    System.out.println("Contains : " + dic.containsKey("hello"));

    IDictionary dic2 = new FastDictionary();
        System.out.println("Size : " + dic2.size());
        System.out.println("Is Empty : " + dic2.IsEmpty());
        dic2.put(0, 0);
        System.out.println("Put value : ('hello' , 'world')" );
        System.out.println("Get : " + dic2.get(0));
        System.out.println("Contains : " + dic2.containsKey("hello"));
    }
}
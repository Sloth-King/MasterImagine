public abstract class AbstractElement {
    private AbstractElement parent;
    private String name;

    public abstract int size();

    public String absoluteAdress(){
        if(this.parent != null) {
            return "/" + this.name;
        }
        else{
            return this.parent.absoluteAdress() + "/" + this.name;
        }
    }





}

public class Main {
    public static void main(String[] args) {
        Produit lgv = new Produit("la grande vadrouille" , 10.0);
        Client cl = new Client("Dupont");
        Compte cmt = new Compte(cl);
        cmt.prixLocation(lgv);
    }
}
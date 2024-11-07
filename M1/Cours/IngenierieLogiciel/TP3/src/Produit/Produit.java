package Produit;

public class Produit{

    private String nom;
    private int prixLocation;
    private int prixVente;

    public Produit(String nom , int prixLocation){
        this.nom = nom;
        this.prixVente = prixVente;
    }

    public int getPrixLocation() {
        return prixLocation;
    }

    public int getPrixVente() {
        return prixVente;
    }

    public String getNom() {
        return nom;
    }

    private void setPrixLocation(int prixLocation) {
        this.prixLocation = prixLocation;
    }

    private void setPrixVente(int prixVente) {
        this.prixVente = prixVente;
    }

}

package Produit;

public class ProduitSolde extends Produit{

    private String nom;
    private int prixLocation;
    private int prixVente;


    public ProduitSolde(String nom , int prixLocation) {
        super(nom,prixLocation);
        this.getPrixVente() = this.prixVente / 2;
    }




}

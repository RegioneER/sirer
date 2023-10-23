package it.cineca.siss.axmr3.sirer.actions;

import it.cineca.siss.axmr3.doc.entities.Element;

import java.util.HashMap;
import java.util.HashSet;

/**
 * Created by vmazzeo on 13/02/2017.
 */
class VoceMonitoraggioFatturazione {
    private HashMap<Element,Integer> list=new HashMap<Element,Integer>();
    private HashSet<Long> pazienti=new HashSet<Long>();
    private Integer numeroPrestazioni=0;
    private Double totale=0.0;
    private HashMap<String,HashMap<String,Double>> cdcs=new HashMap<String, HashMap<String,Double>>();
    private String ssn="";
    private String tp="";
    private String codice="";

    public String getSsn() {
        return ssn;
    }

    public void setSsn(String ssn) {
        this.ssn = ssn;
    }

    public String getTp() {
        return tp;
    }

    public void setTp(String tp) {
        this.tp = tp;
    }

    public String getCodice() {
        return codice;
    }

    public void setCodice(String codice) {
        this.codice = codice;
    }

    public HashMap<String, HashMap<String, Double>> getCdcs() {
        return cdcs;
    }

    public void setCdcs(HashMap<String, HashMap<String, Double>> cdcs) {
        this.cdcs = cdcs;
    }

    public HashMap<Element,Integer> getList() {
        for(Element currElement:list.keySet()){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"debug 2 - element in set - " + currElement.getId().toString());
        }
        return list;
    }

    public void setList(HashMap<Element,Integer> list) {
        this.list = list;
    }

    public HashSet<Long> getPazienti() {
        for(Long currPazz:pazienti){
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"debug - Paziente in set - "+currPazz.toString());
        }
        return pazienti;
    }

    public void setPazienti(HashSet<Long> pazienti) {
        this.pazienti = pazienti;
    }

    public Integer getNumeroPrestazioni() {
        return numeroPrestazioni;
    }

    public void setNumeroPrestazioni(Integer numeroPrestazioni) {
        this.numeroPrestazioni = numeroPrestazioni;
    }

    public Double getTotale() {
        return totale;
    }

    public void setTotale(Double totale) {
        this.totale = totale;
    }

    public void add(Element element,String cdc, String transferPrice, String SSN, String codice, String prezzo){
        add(element, cdc, transferPrice, SSN, codice, prezzo, 1);
    }
    public void add(Element element,String cdc, String transferPrice, String SSN, String codice, String prezzo, Integer quantita){
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Aggiungo voce SSN = "+SSN);
        Element paziente = element.getParent().getParent();
        double valorePrezzo=0.0;
        double valoreTransferPrice=0.0;
        double valoreSSN=0.0;
        double sumCdc=0.0;
        boolean addTransfer=false;
        HashMap<String, Double> emptyCdc = new HashMap<String, Double>();

        emptyCdc.put("TotalePrezzo",0.0);
        emptyCdc.put("TotaleTransferPrice",0.0);
        emptyCdc.put("TotaleSSN",0.0);
        this.ssn=SSN.replaceAll("(,)",".");
        it.cineca.siss.axmr3.log.Log.debug(getClass(),"Aggiungo voce SSN diventa "+this.ssn);
        this.tp=transferPrice;
        this.codice=codice;
        if(!cdcs.containsKey(cdc)){
            cdcs.put(cdc,(HashMap<String, Double>)emptyCdc.clone());
        }
        pazienti.add(paziente.getId());
        numeroPrestazioni+=quantita;
        if(prezzo.matches("-?\\d+(\\.\\d+)?")) {
            valorePrezzo=Double.parseDouble(prezzo)*quantita;
            totale+=valorePrezzo;
            sumCdc=cdcs.get(cdc).get("TotalePrezzo");
            sumCdc+=valorePrezzo;
            cdcs.get(cdc).put("TotalePrezzo",sumCdc);
        }else{
            addTransfer=true;
        }
        if(transferPrice.matches("-?\\d+(\\.\\d+)?")) {
            valoreTransferPrice=Double.parseDouble(transferPrice)*quantita;
            if(addTransfer){
                totale+=valoreTransferPrice;
            }
            sumCdc=cdcs.get(cdc).get("TotaleTransferPrice");
            sumCdc+=valoreTransferPrice;
            cdcs.get(cdc).put("TotaleTransferPrice",sumCdc);
        }
        if(this.ssn.matches("-?\\d+(\\.\\d+)?")) {
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"Aggiungo SSN al totale "+this.ssn);
            valoreSSN=Double.parseDouble(this.ssn)*quantita;
            //totale+=valoreSSN;
            sumCdc=cdcs.get(cdc).get("TotaleSSN");
            sumCdc+=valoreSSN;
            it.cineca.siss.axmr3.log.Log.debug(getClass(),"SSN totale "+sumCdc);
            cdcs.get(cdc).put("TotaleSSN",sumCdc);
        }
        list.put(element,quantita);
    }

    public void addCDC(Element element,String cdc, String transferPrice,  String prezzo, Integer quantita){

        double valorePrezzo=0.0;
        double valoreTransferPrice=0.0;
        double valoreSSN=0.0;
        double sumCdc=0.0;
        boolean addTransfer=false;
        HashMap<String, Double> emptyCdc = new HashMap<String, Double>();

        emptyCdc.put("TotalePrezzo",0.0);
        emptyCdc.put("TotaleTransferPrice",0.0);
        emptyCdc.put("TotaleSSN",0.0);

        if(!cdcs.containsKey(cdc)){
            cdcs.put(cdc,(HashMap<String, Double>)emptyCdc.clone());
        }

        numeroPrestazioni+=quantita;
        if(prezzo.matches("-?\\d+(\\.\\d+)?")) {
            valorePrezzo=Double.parseDouble(prezzo)*quantita;
            totale+=valorePrezzo;
            sumCdc=cdcs.get(cdc).get("TotalePrezzo");
            sumCdc+=valorePrezzo;
            cdcs.get(cdc).put("TotalePrezzo",sumCdc);
        }else{
            addTransfer=true;
        }
        if(transferPrice.matches("-?\\d+(\\.\\d+)?")) {
            valoreTransferPrice=Double.parseDouble(transferPrice)*quantita;
            if(addTransfer){
                totale+=valoreTransferPrice;
            }
            sumCdc=cdcs.get(cdc).get("TotaleTransferPrice");
            sumCdc+=valoreTransferPrice;
            cdcs.get(cdc).put("TotaleTransferPrice",sumCdc);
        }


    }


}
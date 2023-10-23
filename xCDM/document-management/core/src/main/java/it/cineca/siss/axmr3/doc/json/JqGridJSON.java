package it.cineca.siss.axmr3.doc.json;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by giorgio on 17/04/14.
 */
public class JqGridJSON {
    private int rows=0;
    private int total=0;
    private int page=0;
    private List<Object> root=new LinkedList<Object>();

    public int getRows() {
        return rows;
    }

    public void setRows(int rows) {
        this.rows = rows;
    }

    public int getTotal() {
        return total;
    }

    public void setTotal(int total) {
        this.total = total;
    }

    public int getPage() {
        return page;
    }

    public void setPage(int page) {
        this.page = page;
    }

    public List<Object> getRoot() {
        return root;
    }

    public void setRootObjects(List<Object> root) {
        this.root = root;
    }

    public void setRoot(List<ElementJSON> root) {
        this.root=new LinkedList<Object>();
        for (int i=0;i<root.size();i++){
            this.root.add(root.get(i));
        }
    }
}

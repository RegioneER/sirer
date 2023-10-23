package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseFile;

import javax.persistence.*;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 31/07/13
 * Time: 12.30
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_OBJ_FILE")
public class File extends BaseFile<FileContent> {


}

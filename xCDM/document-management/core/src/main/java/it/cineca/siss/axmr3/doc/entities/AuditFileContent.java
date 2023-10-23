package it.cineca.siss.axmr3.doc.entities;

import it.cineca.siss.axmr3.doc.entities.base.BaseFileContent;

import javax.persistence.Entity;
import javax.persistence.Table;

/**
 * Created with IntelliJ IDEA.
 * User: Carlo
 * Date: 09/09/13
 * Time: 14.03
 * To change this template use File | Settings | File Templates.
 */
@Entity
@Table (name = "DOC_AUDIT_FILE_CONTENT")
public class AuditFileContent extends BaseFileContent {
}

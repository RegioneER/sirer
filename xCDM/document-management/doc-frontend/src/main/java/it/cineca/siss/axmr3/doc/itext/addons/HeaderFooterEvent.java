package it.cineca.siss.axmr3.doc.itext.addons;

import com.itextpdf.text.*;
import com.itextpdf.text.pdf.BaseFont;
import com.itextpdf.text.pdf.ColumnText;
import com.itextpdf.text.pdf.PdfPageEventHelper;
import com.itextpdf.text.pdf.PdfWriter;
import com.itextpdf.tool.xml.XMLWorker;
import com.itextpdf.tool.xml.XMLWorkerFontProvider;

import java.io.IOException;

/**
 * Created by cin0562a on 28/10/14.
 */
public class HeaderFooterEvent extends PdfPageEventHelper {
    /** Alternating phrase for the header. */
    //Phrase[] header = new Phrase[2];
    /**
     * Current page number (will be reset for every chapter).
     */
    protected int pagenumber;
    protected int totalPages;
    protected Phrase header;
    protected Phrase footer;
    protected XMLWorkerFontProvider fontProvider;

    public void init(String header, String footer, int totalPages, XMLWorkerFontProvider fontProvider) {
        this.fontProvider = fontProvider;
        Font font = fontProvider.getFont("Times New Roman", 10, Font.NORMAL);
        this.totalPages = totalPages;
        it.cineca.siss.axmr3.log.Log.info(getClass(),"\n\n\n font: " + FontFactory.TIMES + " - " + FontFactory.TIMES_ROMAN);
        this.header = new Phrase(header, font);
        this.footer = new Phrase(footer, font);
    }

    /**
     * Initialize one of the headers.
     *
     * @see com.itextpdf.text.pdf.PdfPageEventHelper#onOpenDocument(
     *com.itextpdf.text.pdf.PdfWriter, com.itextpdf.text.Document)
     */
    public void onOpenDocument(PdfWriter writer, Document document) {
        //    header[0] = new Phrase("Movie history");
    }

    /**
     * Initialize one of the headers, based on the chapter title;
     * reset the page number.
     *
     * @see com.itextpdf.text.pdf.PdfPageEventHelper#onChapter(
     *com.itextpdf.text.pdf.PdfWriter, com.itextpdf.text.Document, float,
     * com.itextpdf.text.Paragraph)
     */
    public void onChapter(PdfWriter writer, Document document,
                          float paragraphPosition, Paragraph title) {
        //    header[1] = new Phrase(title.getContent());
        //    pagenumber = 1;
    }

    /**
     * Increase the page number.
     *
     * @see com.itextpdf.text.pdf.PdfPageEventHelper#onStartPage(
     *com.itextpdf.text.pdf.PdfWriter, com.itextpdf.text.Document)
     */
    public void onStartPage(PdfWriter writer, Document document) {
        pagenumber++;
    }

    /**
     * Adds the header and the footer.
     *
     * @see com.itextpdf.text.pdf.PdfPageEventHelper#onEndPage(
     *com.itextpdf.text.pdf.PdfWriter, com.itextpdf.text.Document)
     */
    public void onEndPage(PdfWriter writer, Document document) {
        Rectangle rect = writer.getBoxSize("art");
        ColumnText.showTextAligned(writer.getDirectContent(),
                Element.ALIGN_LEFT, header,
                rect.getLeft(), rect.getTop(), 0);
        String pageString = String.format("%d/%d", pagenumber, totalPages);
        Font font = fontProvider.getFont("Times New Roman", 10, Font.ITALIC);
        Phrase page = new Phrase(pageString, font);
        ColumnText.showTextAligned(writer.getDirectContent(),
                Element.ALIGN_RIGHT, page,
                rect.getRight(), rect.getBottom() - 10, 0);
        ColumnText.showTextAligned(writer.getDirectContent(),
                Element.ALIGN_CENTER, footer,
                (rect.getLeft() + rect.getRight()) / 2, rect.getBottom() - 30, 0);
    }
}

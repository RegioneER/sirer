import com.itextpdf.text.Document;
import com.itextpdf.text.DocumentException;
import com.itextpdf.text.pdf.PdfWriter;
import com.itextpdf.tool.xml.XMLWorkerHelper;
import org.hsqldb.lib.StringInputStream;

import java.io.*;

/**
 * Created by cin0562a on 24/10/14.
 */
public class iTextTest {


    public static void main(String[] argv) throws IOException, DocumentException {
        String content = readFile("/Users/cin0562a/Desktop/test.html");
        //content="<html><body><p>This is my Project</p></body></html>";
        Document document = new Document();
        FileOutputStream fOut = new FileOutputStream("/Users/cin0562a/Desktop/test.pdf");
        PdfWriter writer = PdfWriter.getInstance(document, fOut);
        document.open();
        XMLWorkerHelper worker = XMLWorkerHelper.getInstance();
        it.cineca.siss.axmr3.log.Log.info(getClass(),content);
        //worker.parseXHtml(writer, document, new StringReader("<html><body> This is my Project </body></html>"));
        worker.parseXHtml(writer, document, new StringReader(content));
        document.close();
        fOut.close();
    }

    private static String readFile(String file) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String line = null;
        StringBuilder stringBuilder = new StringBuilder();
        String ls = System.getProperty("line.separator");

        while ((line = reader.readLine()) != null) {
            stringBuilder.append(line);
            stringBuilder.append(ls);
        }

        return stringBuilder.toString();
    }


}

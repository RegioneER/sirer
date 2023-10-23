package it.cineca.siss.axmr3.doc.itext.addons;


import com.itextpdf.text.BadElementException;
import com.itextpdf.text.Chunk;
import com.itextpdf.text.Element;
import com.itextpdf.text.pdf.codec.Base64;
import com.itextpdf.tool.xml.NoCustomContextException;
import com.itextpdf.tool.xml.Tag;
import com.itextpdf.tool.xml.WorkerContext;
import com.itextpdf.tool.xml.exceptions.RuntimeWorkerException;
import com.itextpdf.tool.xml.html.HTML;
import com.itextpdf.text.Image;
import com.itextpdf.tool.xml.pipeline.html.HtmlPipelineContext;
import it.cineca.siss.axmr3.web.freemarker.AxmrFreemarkerConfigurer;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Created by cin0562a on 28/10/14.
 */
public class ImageTagProcessor extends com.itextpdf.tool.xml.html.Image {

    protected String imagePath;
    
    protected static final Logger log=Logger.getLogger(ImageTagProcessor.class);

    public String getImagePath() {
        return imagePath;
    }

    public void setImagePath(String imagePath) {
        this.imagePath = imagePath;
    }

    /*
             * (non-Javadoc)
             *
             * @see com.itextpdf.tool.xml.TagProcessor#endElement(com.itextpdf.tool.xml.Tag, java.util.List, com.itextpdf.text.Document)
             */
    @Override
    public List<Element> end(final WorkerContext ctx, final Tag tag, final List<Element> currentContent) {
        final Map<String, String> attributes = tag.getAttributes();
        String src = attributes.get(HTML.Attribute.SRC);
        List<Element> elements = new ArrayList<Element>(1);
        if (null != src && src.length() > 0) {
            Image img = null;
            if (src.startsWith("data:image/")) {
                final String base64Data = src.substring(src.indexOf(",") + 1);
                try {
                    img = Image.getInstance(Base64.decode(base64Data));
                } catch (Exception e) {
                    log.error(e.getMessage(),e);
                }
            } else {
                try {
                    img = Image.getInstance(imagePath + "/templates/documents/pdf/" + src);
                } catch (BadElementException e) {
                    log.error(e.getMessage(),e);
                } catch (IOException e) {
                    log.error(e.getMessage(),e);
                }
            }
            if (img != null) {
                if (attributes.get(HTML.Attribute.WIDTH) != null && attributes.get(HTML.Attribute.HEIGHT) != null) {
                    img.scaleToFit(Float.parseFloat(attributes.get(HTML.Attribute.WIDTH)), Float.parseFloat(attributes.get(HTML.Attribute.HEIGHT)));
                }
                try {
                    final HtmlPipelineContext htmlPipelineContext = getHtmlPipelineContext(ctx);
                    elements.add(getCssAppliers().apply(new Chunk((com.itextpdf.text.Image) getCssAppliers().apply(img, tag, htmlPipelineContext), 0, 0, true), tag,
                            htmlPipelineContext));
                } catch (NoCustomContextException e) {
                    throw new RuntimeWorkerException(e);
                }
            } else {
                elements = super.end(ctx, tag, currentContent);
            }
        }
        return elements;
    }
}
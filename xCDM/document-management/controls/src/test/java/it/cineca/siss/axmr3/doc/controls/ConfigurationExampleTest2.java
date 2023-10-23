package it.cineca.siss.axmr3.doc.controls;

import com.google.gson.Gson;
import it.cineca.siss.axmr3.controls.JsBuilder;
import it.cineca.siss.axmr3.doc.controls.json.Configuration;

import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;

/**
 * Created by Carlo on 13/09/2016.
 */
public class ConfigurationExampleTest2 {

    public static void main(String[] argv) throws IOException {
        String json=readFile("C:\\Users\\Carlo\\Progetti\\xCDM\\document-management\\controls\\src\\test\\resources\\test2.json", Charset.defaultCharset());
        Gson gson = new Gson();
        Configuration jsonCfg=gson.fromJson(json,Configuration.class);



    }


    static String readFile(String path, Charset encoding)
            throws IOException
    {
        byte[] encoded = Files.readAllBytes(Paths.get(path));
        return new String(encoded, encoding);
    }

}

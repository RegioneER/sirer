package it.cineca.siss.axmr3.authentication;

import org.apache.log4j.Logger;
import org.springframework.security.authentication.encoding.PasswordEncoder;
import org.springframework.security.crypto.bcrypt.BCrypt;

import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Created with IntelliJ IDEA.
 * User: cin0562a
 * Date: 24/10/13
 * Time: 17:08
 * To change this template use File | Settings | File Templates.
 */
public class IanusPasswordEncoder implements PasswordEncoder {

    static final Logger log=Logger.getLogger(IanusPasswordEncoder.class);

    public String encodePassword(String rawPass, Object salt) {
        return null;  //To change body of implemented methods use File | Settings | File Templates.
    }

    public boolean isPasswordValid(String encPass, String rawPass, Object salt) {
        try {
            String[] split=encPass.split("\\$");
            return MD5Crypt.crypt(rawPass.toUpperCase(), split[2]).equals(encPass) || BCrypt.checkpw(rawPass.toUpperCase(),encPass)  || BCrypt.checkpw(rawPass,encPass);
        } catch (Exception e) {
            log.error(e.getMessage(),e);  //To change body of catch statement use File | Settings | File Templates.
            return false;
        }

    }
}

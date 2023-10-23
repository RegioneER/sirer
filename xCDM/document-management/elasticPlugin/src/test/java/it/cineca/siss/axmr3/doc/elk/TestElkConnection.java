package it.cineca.siss.axmr3.doc.elk;

import org.elasticsearch.action.search.SearchRequestBuilder;
import org.elasticsearch.action.search.SearchResponse;
import org.elasticsearch.action.search.SearchType;
import org.elasticsearch.client.Client;
import org.elasticsearch.client.transport.TransportClient;
import org.elasticsearch.common.settings.Settings;
import org.elasticsearch.common.transport.InetSocketTransportAddress;
import org.elasticsearch.index.query.QueryBuilder;
import org.elasticsearch.search.sort.SortOrder;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.HashMap;

import static org.elasticsearch.index.query.QueryBuilders.matchAllQuery;

/**
 * Created by Carlo on 29/01/2016.
 */
public class TestElkConnection {



    public static void main(String[] argv) throws UnknownHostException {
        Settings settings = Settings.settingsBuilder().put("cluster.name", "siss-elastic-prod-01").build();
        TransportClient.Builder tbld = TransportClient.builder();
        tbld.settings(settings);
        Client client = tbld.build().addTransportAddress(new InetSocketTransportAddress(InetAddress.getByName("siss31.private.cineca.it"), 9300));
        String indexName="refil-full";
        String type="Corso";
        String query="" +
                //"{\"query\":" +
                "{" +
                "\"and\":[\n" +
                "          {\n" +
                "            \"bool\":{\n" +
                "              \"should\":[\n" +
                "{\n" +
                "                  \"terms\" : { \"viewableByUsers\" : [\"formazione-niguarda\",\"*\"] }\n" +
                "                },\n" +
                "                {\n" +
                "                  \"terms\" : { \"viewableByGroups\" : [\"tech-admin\",\"ctc\"] }\n" +
                "                }              ]\n" +
                "            }\n" +
                "          },\n" +
                //"        {\"missing\": {\"field\" : \"metadata.statoValidazioneCentro\"}}"+
                "      ]" +
                "}" +
                //",\"sort\":[{\"id\":{\"order\":\"asc\"}}]" +
                //"}" +
                "\n";
        HashMap<String,String> postFilter = new HashMap<String,String>();
        postFilter.put("metadata.CorsoWF.values.Ente_FLOATVALUE","1");
        postFilter.put("metadata.CorsoRegistrazione_ResponsabileScientifico","CGNWLM65P55F205D");
        SearchRequestBuilder requestBuilder = client.prepareSearch(indexName).setPostFilter(postFilter).setTypes(type.toLowerCase()).setSearchType(SearchType.DEFAULT);
        SortOrder smod = SortOrder.DESC;
        String sidx = "metadata.CorsoRegistrazione.values.SCSS";
        String sord = "asc";
        int page=1;
        int rpp=2000; //results per page?
        int start = (page - 1) * rpp;
        if (sidx!=null && !sidx.isEmpty()){
            if (sord!=null && !sord.isEmpty()){
                if (sord.toLowerCase().equals("desc")){
                    smod=SortOrder.DESC;
                }else {
                    smod=SortOrder.ASC;
                }
            }
        }else {
            sidx="id";
        }
        //setPostFilter(query)
        requestBuilder.addSort(sidx, smod)
                .setFrom(start).setSize(rpp).setExplain(true);
        //if (!fields) requestBuilder.setNoFields();
        System.out.println(requestBuilder.toString());
        //SearchResponse response=requestBuilder.execute().actionGet();
        //System.out.println(response.toString());
        System.out.println("Fatto");
        /*
        Settings settings = Settings.settingsBuilder().put("cluster.name", "siss-elastic-dev-01").build();
        TransportClient.Builder bld = TransportClient.builder();
        bld.settings(settings);

        Client client = bld.build()
                .addTransportAddress(new InetSocketTransportAddress(InetAddress.getByName("siss27.private.cineca.it"), 9300));
        QueryBuilder qb = QueryBuilders.matchQuery("parent.metadata.IdCentro.values.PI", "Barone Carlo ");
        */
    }

}

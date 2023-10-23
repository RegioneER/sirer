package it.cineca.siss.axmr3.doc.elk;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import it.cineca.siss.axmr3.authentication.IAuthority;
import it.cineca.siss.axmr3.authentication.IUser;
import it.cineca.siss.axmr3.doc.beans.InternalServiceBean;
import it.cineca.siss.axmr3.doc.entities.Element;
import it.cineca.siss.axmr3.doc.entities.ElkIndexesStatus;
import it.cineca.siss.axmr3.doc.web.exceptions.RestException;
import it.cineca.siss.axmr3.doc.web.services.DocumentService;
import it.cineca.siss.axmr3.exceptions.AxmrGenericException;
import it.cineca.siss.axmr3.hibernate.BaseDao;
import it.cineca.siss.axmr3.log.Log;
import it.cineca.siss.axmr3.transactions.MultiSessionTXManager;
import org.apache.log4j.Logger;
import org.elasticsearch.action.admin.indices.mapping.put.PutMappingRequest;
import org.elasticsearch.action.admin.indices.mapping.put.PutMappingResponse;
import org.elasticsearch.action.delete.DeleteRequest;
import org.elasticsearch.action.delete.DeleteResponse;
import org.elasticsearch.action.index.IndexRequest;
import org.elasticsearch.action.index.IndexResponse;
import org.elasticsearch.action.search.SearchRequestBuilder;
import org.elasticsearch.action.search.SearchResponse;
import org.elasticsearch.action.search.SearchType;
import org.elasticsearch.client.Client;
import org.elasticsearch.client.transport.TransportClient;
import org.elasticsearch.common.settings.Settings;
import org.elasticsearch.common.transport.InetSocketTransportAddress;
import org.elasticsearch.index.query.QueryBuilder;
import org.elasticsearch.search.SearchHit;
import org.elasticsearch.search.sort.SortOrder;
import org.hibernate.Criteria;
import org.hibernate.SQLQuery;
import org.hibernate.criterion.*;
import org.springframework.beans.factory.InitializingBean;
import org.springframework.beans.factory.annotation.Autowired;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.*;

import static org.elasticsearch.index.query.QueryBuilders.matchAllQuery;

/**
 * Created by Carlo on 29/01/2016.
 */
public class ElkService implements InitializingBean {

    private String clusterName;
    private String elkHosts;
    private String indexPrefix;
    protected String fieldIndexObjs;
    protected String fullIndexObjs;
    protected String fullIndexWithParentsObjs;
    protected List<String> fieldIndexObjsList;
    protected List<String> fullIndexObjsList;
    protected List<String> fullIndexWithParentsObjsList;
    private BaseDao<ElkIndexesStatus> isDao;
    private MultiSessionTXManager globalTx;
    //private TransportClient client;
    private TransportClient.Builder tbld;
    private InetSocketTransportAddress[] addresses;

    @Autowired
    protected InternalServiceBean isb;

    public InternalServiceBean getIsb() {
        return isb;
    }

    public void setIsb(InternalServiceBean isb) {
        this.isb = isb;
    }


    public String getFullIndexWithParentsObjs() {
        return fullIndexWithParentsObjs;
    }

    public void setFullIndexWithParentsObjs(String fullIndexWithParentsObjs) {
        this.fullIndexWithParentsObjs = fullIndexWithParentsObjs;
    }

    public String getFieldIndexObjs() {
        return fieldIndexObjs;
    }

    public void setFieldIndexObjs(String fieldIndexObjs) {
        this.fieldIndexObjs = fieldIndexObjs;
    }

    public String getFullIndexObjs() {
        return fullIndexObjs;
    }

    public void setFullIndexObjs(String fullIndexObjs) {
        this.fullIndexObjs = fullIndexObjs;
    }

    public void saveIdxStatusWriteDB(String indexName, String type, Long objId) throws AxmrGenericException {
        String txName = "doc";
        isDao = new BaseDao<ElkIndexesStatus>(docService.getTxManager(), txName, ElkIndexesStatus.class);
        Criteria c = isDao.getCriteria();
        c.add(Restrictions.eq("indexName", indexName))
                .add(Restrictions.eq("objType", type))
                .add(Restrictions.eq("objId", objId))
                .add(Restrictions.eq("instance", this.clusterName))
        ;
        ElkIndexesStatus elIdx = (ElkIndexesStatus) c.uniqueResult();
        //Log.info(this.getClass(),"SAVEIDXSTATUS - cerco record: "+indexName+" - "+type+" - "+objId);
        if (elIdx == null) {
            //Log.info(this.getClass(),"SAVEIDXSTATUS-INSERT - non trovo record e lo creo: "+indexName+" - "+type+" - "+objId);
            elIdx = new ElkIndexesStatus();
            elIdx.setIndexName(indexName);
            elIdx.setObjId(objId);
            elIdx.setObjType(type);
            elIdx.setInstance(this.clusterName);
            elIdx.setLastUpdateDt(new GregorianCalendar());
        } else {
            //Log.info(this.getClass(),"SAVEIDXSTATUS-UPD - trovo record e lo aggiorno: "+indexName+" - "+type+" - "+objId);
            elIdx.setLastUpdateDt(new GregorianCalendar());
        }
        isDao.saveOrUpdate(elIdx);
        docService.getTxManager().commitAndKeepAlive();
        Log.info(this.getClass(), "SAVEIDXSTATUS-DONE: " + indexName + " - " + type + " - " + objId);
    }

    public void saveIdxStatus(String indexName, String type, Long objId) throws AxmrGenericException {
        //Log.info(this.getClass(),"Chiamata SaveIdxStatus");
        //if (isb.isActive()){
        //    Log.info(this.getClass()," - effettuo chiamata isb a /rest/elk/saveIdxStatus/"+indexName+"/"+type+"/"+objId);
        //    isb.doInternalSyncRequest("/rest/elk/saveIdxStatus/"+indexName+"/"+type+"/"+objId);
        //}else{
        Log.info(this.getClass(), " - effettuo scrittura diretta su DB");
        saveIdxStatusWriteDB(indexName, type, objId);
        //}
    }

    public void initDocumentService(MultiSessionTXManager globalTx) throws Exception {
        docService = new DocumentService();
        this.globalTx = globalTx;
        String txName = "doc";
        docService.setTxManager(globalTx);
        if (docService.getAxmr3txManager() != null) docService.setTxManager(docService.getAxmr3txManager());
        docService.afterPropertiesSet();
    }

    public String getElkHosts() {
        return elkHosts;
    }

    public void setElkHosts(String elkHosts) {
        this.elkHosts = elkHosts;
    }

    public String getClusterName() {
        return clusterName;
    }

    public void setClusterName(String clusterName) {
        this.clusterName = clusterName;
    }

    public String getIndexPrefix() {
        return indexPrefix;
    }

    public void setIndexPrefix(String indexPrefix) {
        this.indexPrefix = indexPrefix;
    }

    @Autowired
    protected DocumentService docService;

    public DocumentService getDocService() {
        return docService;
    }

    public void setDocService(DocumentService docService) {
        this.docService = docService;
    }

    public void afterPropertiesSet() throws Exception {
        fieldIndexObjsList = new LinkedList<String>();
        fullIndexObjsList = new LinkedList<String>();
        fullIndexWithParentsObjsList = new LinkedList<String>();
        if (!fieldIndexObjs.isEmpty()) {
            fieldIndexObjsList = Arrays.asList(fieldIndexObjs.toLowerCase().split(","));
        }
        if (!fullIndexObjs.isEmpty()) {
            fullIndexObjsList = Arrays.asList(fullIndexObjs.toLowerCase().split(","));
        }
        if (!fullIndexWithParentsObjs.isEmpty()) {
            fullIndexWithParentsObjsList = Arrays.asList(fullIndexWithParentsObjs.toLowerCase().split(","));
        }
    }


    public List<ElkSimpleElement> getAll(String type) {
        Criteria c = docService.getDocDAO().getCriteria();
        Long typeId = docService.getTypeIdByNameOrId(type);
        docService.getType(typeId);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(Restrictions.eq("type.id", typeId))
                .add(Restrictions.eq("deleted", false));
        List<Element> els = c.list();
        List<ElkSimpleElement> ret = new LinkedList<ElkSimpleElement>();
        for (Element el : els) {
            ret.add(ElkSimpleElement.elementToSimpleWithParents(el));
        }
        return ret;
    }

    public Client getNewClient() throws UnknownHostException {
        if (this.tbld == null) {
            Settings settings = Settings.settingsBuilder().put("cluster.name", this.clusterName).build();
            this.tbld = TransportClient.builder();
            this.tbld.settings(settings);
            String[] split1 = this.elkHosts.split(",");
            this.addresses = new InetSocketTransportAddress[split1.length];
            for (int i = 0; i < split1.length; i++) {
                String[] split2 = split1[i].split(":");
                this.addresses[i] = new InetSocketTransportAddress(InetAddress.getByName(split2[0]), Integer.parseInt(split2[1]));
            }
        }
        Client newclient = this.tbld.build().addTransportAddresses(addresses);
        return newclient;
    }

    public void simpleIndex(Long elId) throws UnknownHostException, AxmrGenericException {
        simpleIndex(docService.getDocDAO().getById(elId));
    }

    public void simpleIndex(Element el) throws UnknownHostException, AxmrGenericException {

        Log.info(this.getClass(), " - Controllo che l'indice dell'elemento non sia stato aggiornato nel frattempo el:" + el.getId() + " di tipo " + el.getTypeName());
        isDao = new BaseDao<ElkIndexesStatus>(docService.getTxManager(), "doc", ElkIndexesStatus.class);

        Criteria c = isDao.getCriteria();
        c.add(Restrictions.eq("indexName", "simple"))
                .add(Restrictions.eq("objType", el.getTypeName()))
                .add(Restrictions.eq("instance", this.clusterName))
                .add(Restrictions.eq("objId", el.getId()));
        ElkIndexesStatus elIdx = (ElkIndexesStatus) c.uniqueResult();
        if (elIdx != null) {
            if (el.getLastUpdateDt() != null) {
                if (elIdx.getLastUpdateDt().after(el.getLastUpdateDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di ultima modifica el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            } else {
                if (elIdx.getLastUpdateDt().after(el.getCreationDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di creazione elemento non modificato el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            }
        }


        Client elkClient = getNewClient();
        String type = el.getTypeName();
        ElkSimpleElement tsel = new ElkSimpleElement();
        IndexRequest tindexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), "testEl");
        tindexRequest.source(new Gson().toJson(tsel));
        IndexResponse tresponse = elkClient.index(tindexRequest).actionGet();
        if (el.isDeleted()) {
            DeleteRequest deleterequest = new DeleteRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), el.getId() + "");
            DeleteResponse response = elkClient.delete(deleterequest).actionGet();
            if (response != null && response.getShardInfo().getFailed() == 0) { // && response.isFound()) {
                saveIdxStatus("simple", type, el.getId());
            } else {
                //Index error
                Log.error(this.getClass(), "Index error");
                Log.error(this.getClass(), "RESPONSE: " + response);
            }
        } else {
            ElkSimpleElement sel = ElkSimpleElement.elementToSimple(el);
            String json = new Gson().toJson(sel);
            IndexRequest indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), el.getId() + "");
            indexRequest.source(json);
            IndexResponse response = elkClient.index(indexRequest).actionGet();
            if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {
                saveIdxStatus("simple", type, el.getId());
            } else {
                //Index error
                Log.error(this.getClass(), "Index error");
                //Log.info(this.getClass(),"RESPONSE: "+response);
            }

        }
        elkClient.close();
    }


    public void doSimpleIndex(String type) throws AxmrGenericException, UnknownHostException {
        doSimpleIndex(type, false);
    }

    public void doSimpleIndex(String type, boolean forceAll) throws UnknownHostException, AxmrGenericException {
        Criteria c = docService.getDocDAO().getCriteria("main");
        Long typeId = docService.getTypeIdByNameOrId(type);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(Restrictions.eq("main.type.id", typeId));
        if (!forceAll) {
            DetachedCriteria dateJoin = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub");
            dateJoin.add(Restrictions.eqProperty("sub.objId", "main.id"));
            dateJoin.add(Restrictions.eq("sub.indexName", "simple"));
            dateJoin.setProjection(Property.forName("sub.lastUpdateDt"));
            DetachedCriteria subCriteria = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub2");
            subCriteria.add(Restrictions.eq("sub2.indexName", "simple"));
            subCriteria.add(Restrictions.eq("sub2.objType", type));
            subCriteria.setProjection(Property.forName("sub2.objId"));
            c.add(
                    Restrictions.or(
                            Subqueries.propertyGe("main.lastUpdateDt", dateJoin),
                            Subqueries.propertyNotIn("main.id", subCriteria)
                    )
            );
        }
        List<Element> els = c.list();
        for (Element el : els) {
            simpleIndex(el);
        }
    }

    public void customIndex(Long elId, String indexSuffix) throws UnknownHostException, AxmrGenericException {
        customIndex(docService.getDocDAO().getById(elId), indexSuffix);
    }

    public void customIndex(Element el, String indexSuffix) throws UnknownHostException, AxmrGenericException {
        Client elkClient = getNewClient();
        String type = el.getTypeName();
        ElkSimpleElement tsel = new ElkSimpleElement();
        IndexRequest tindexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-" + indexSuffix, type.toLowerCase(), "testEl");
        tindexRequest.source(new Gson().toJson(tsel));
        IndexResponse tresponse = elkClient.index(tindexRequest).actionGet();
        if (el.isDeleted()) {
            DeleteRequest deleterequest = new DeleteRequest(indexPrefix.toLowerCase() + "-" + indexSuffix, type.toLowerCase(), el.getId() + "");
            DeleteResponse response = elkClient.delete(deleterequest).actionGet();
            if (response != null && response.getShardInfo().getFailed() == 0) { // && response.isFound()) {
                saveIdxStatus("simple", type, el.getId());
            } else {
                //Index error
                Log.error(this.getClass(), "Index error");
                Log.error(this.getClass(), "RESPONSE: " + response);
            }
        } else {
            ElkSimpleElement sel = ElkSimpleElement.elementToSimple(el);
            String json = new Gson().toJson(sel);
            IndexRequest indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-" + indexSuffix, type.toLowerCase(), el.getId() + "");
            indexRequest.source(json);
            IndexResponse response = elkClient.index(indexRequest).actionGet();
            if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {
                saveIdxStatus(indexSuffix, type, el.getId());
            } else {
                //Index error
                Log.error(this.getClass(), "Index error");
                Log.error(this.getClass(), "RESPONSE: " + response);
            }
        }
        elkClient.close();
    }


    public void doCustomIndex(String type, String indexSuffix) throws AxmrGenericException, UnknownHostException {
        doCustomIndex(type, indexSuffix, false);
    }

    public void doCustomIndex(String type, String indexSuffix, boolean forceAll) throws UnknownHostException, AxmrGenericException {
        Criteria c = docService.getDocDAO().getCriteria("main");
        Long typeId = docService.getTypeIdByNameOrId(type);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(Restrictions.eq("main.type.id", typeId));
        if (!forceAll) {
            DetachedCriteria dateJoin = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub");
            dateJoin.add(Restrictions.eqProperty("sub.objId", "main.id"));
            dateJoin.add(Restrictions.eq("sub.indexName", indexSuffix));
            dateJoin.setProjection(Property.forName("sub.lastUpdateDt"));
            DetachedCriteria subCriteria = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub2");
            subCriteria.add(Restrictions.eq("sub2.indexName", indexSuffix));
            subCriteria.add(Restrictions.eq("sub2.objType", type));
            subCriteria.setProjection(Property.forName("sub2.objId"));
            c.add(
                    Restrictions.or(
                            Subqueries.propertyGe("main.lastUpdateDt", dateJoin),
                            Subqueries.propertyNotIn("main.id", subCriteria)
                    )
            );
        }
        List<Element> els = c.list();
        if (els != null) {
            for (Element el : els) {
                customIndex(el, indexSuffix);
            }
        }
    }

    public void elementIdxUpdate(Element el) throws AxmrGenericException, UnknownHostException {
        //VMAZZEO//Log.info(this.getClass()," - - ### Avvio indicizzazione elementIdxUpdate elemento "+el.getId()+" ("+el.getTypeName()+")");
        Element parent = el.getParent();
        if (parent != null) {
            fullIndex(parent);
            while (parent.getParent() != null) {
                parent = parent.getParent();
                fullIndex(parent);
            }
        }
        fullIndex(el);
        fieldIndex(el);
    }


    public void fieldIndex(Long elId) throws UnknownHostException, AxmrGenericException {
        fieldIndex(docService.getDocDAO().getById(elId));
    }

    public void fieldIndex(Element el) throws UnknownHostException, AxmrGenericException {
        if (fieldIndexObjsList.size() > 0 && !fieldIndexObjsList.contains(el.getTypeName().toLowerCase())) {
            //VMAZZEO//Log.info(this.getClass()," - ###ELK escludo indicizzazione fields elemento "+el.getId()+" di tipo "+el.getTypeName());
            return;
        } else if (fieldIndexObjsList.size() == 0 && !el.getType().isSearchable()) {
            //VMAZZEO//Log.info(this.getClass()," - ###ELK escludo indicizzazione (isSearchable) fields elemento "+el.getId()+" di tipo "+el.getTypeName());
            return;
        }
        //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX! - elemento "+el.getId()+" di tipo "+el.getTypeName());
        String type = el.getTypeName();
        Log.info(this.getClass(), " - Controllo che l'indice dell'elemento non sia stato aggiornato nel frattempo el:" + el.getId() + " di tipo " + el.getTypeName());
        isDao = new BaseDao<ElkIndexesStatus>(docService.getTxManager(), "doc", ElkIndexesStatus.class);

        Criteria c = isDao.getCriteria();
        c.add(Restrictions.eq("indexName", "field"))
                .add(Restrictions.eq("objType", el.getTypeName()))
                .add(Restrictions.eq("instance", this.clusterName))
                .add(Restrictions.eq("objId", el.getId()));
        ElkIndexesStatus elIdx = (ElkIndexesStatus) c.uniqueResult();
        if (elIdx != null) {
            if (el.getLastUpdateDt() != null) {
                if (elIdx.getLastUpdateDt().after(el.getLastUpdateDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di ultima modifica el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            } else {
                if (elIdx.getLastUpdateDt().after(el.getCreationDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di creazione elemento non modificato el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            }
        }


        Client elkClient = getNewClient();
        ElkValue tel = new ElkValue();
        IndexRequest tindexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-fields", type.toLowerCase(), el.getId() + "");
        tindexRequest.source(new Gson().toJson(tel));
        IndexResponse tresponse = elkClient.index(tindexRequest).actionGet();

        //VMAZZEO//Log.info(this.getClass(),"PREPARE indice fields - tipo "+type.toLowerCase()+" - id: "+el.getId());
        Map<String, Object> maps = new HashMap<String, Object>();
        maps.put("date_detection", true);
        LinkedList<Object> templates = new LinkedList<Object>();
        Map<String, ElkTemplate> singleTemplate = new HashMap<String, ElkTemplate>();
        singleTemplate.put("noanafields",new ElkTemplate("*_NOTANALYZED","*", new ElkMapping("string","not_analyzed")));
        templates.add(singleTemplate);
        singleTemplate = new HashMap<String,ElkTemplate>();
        singleTemplate.put("codefields",new ElkTemplate("*_CODE","*", new ElkMapping("string","not_analyzed")));
        templates.add(singleTemplate);
        maps.put("dynamic_templates", templates);
        //VMAZZEO//Log.info(this.getClass(), new Gson().toJson(maps));
        PutMappingResponse putMappingResponse = elkClient.admin().indices()
                .preparePutMapping(indexPrefix.toLowerCase() + "-fields")
                .setType(type.toLowerCase())
                .setSource(new Gson().toJson(maps))
                .execute().actionGet();
        //Log.warn(this.getClass(), putMappingResponse.toString());

        if (el.isDeleted()) {
            //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 1 - elemento "+el.getId()+" eliminato !!!");
            QueryBuilder qb = matchAllQuery();
            String queryFilterObjId = "{\n" +
                    "  \"query\": {\n" +
                    "    \"filtered\": {\n" +
                    "      \"query\": {\n" +
                    "        \"match_all\": {}\n" +
                    "      },\n" +
                    "      \"filter\":\n" +
                    "{\"and\":[\n" +
                    "     {\"term\": {\"objId\": " + el.getId() + "}}\n" +
                    "]}\n" +
                    "}\n" +
                    "  }}";
            SearchRequestBuilder requestBuilder = elkClient.prepareSearch(indexPrefix.toLowerCase() + "-fields").setTypes(type.toLowerCase()).setSearchType(SearchType.DEFAULT).setQuery(qb)
                    .setPostFilter(queryFilterObjId).setExplain(true);
            SearchResponse response = requestBuilder.execute().actionGet();
            if (response.getHits().getTotalHits() > 0) {
                for (int i = 0; i < response.getHits().getHits().length; i++) {
                    String id = response.getHits().getHits()[i].getId();
                    DeleteRequest deleterequest = new DeleteRequest(indexPrefix.toLowerCase() + "-fields", type.toLowerCase(), id);
                    Log.info(this.getClass(), "PROVO AD ELIMINARE: " + indexPrefix.toLowerCase() + "-fields " + type.toLowerCase() + " " + id);
                    DeleteResponse delResponse = elkClient.delete(deleterequest).actionGet();
                    if (delResponse != null && delResponse.getShardInfo().getFailed() == 0) { // && delResponse.isFound()){
                        //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 1.1 - trovo elemento "+el.getId()+" e lo elimino !!!");
                        //    saveIdxStatus("fields", type, el.getId());
                    } else {
                        //Index error
                        Log.error(this.getClass(), "Index error");
                        //Log.info(this.getClass(),"RESPONSE: "+response);
                    }
                }
            } else {
                //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 1.2 - non trovo elemento "+el.getId()+" ma aggiorno indice per non riprocessarlo nuovamente!!!");
                //    saveIdxStatus("fields", type, el.getId());
            }
            saveIdxStatus("fields", type, el.getId());
        } else {
            //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 2 recupero valori - elemento "+el.getId()+" di tipo "+el.getTypeName());
            List<ElkValue> vals = ElkValue.buildValues(el);
            //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 3 trovati "+vals.size()+" valori - elemento "+el.getId()+" di tipo "+el.getTypeName());
            boolean error = false;
            for (int i = 0; i < vals.size(); i++) {
                String json1 = new Gson().toJson(vals.get(i));
                IndexRequest indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-fields", type.toLowerCase(), vals.get(i).getId());
                indexRequest.source(json1);
                IndexResponse response = elkClient.index(indexRequest).actionGet();
                if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {

                } else {
                    //Index error
                    Log.error(this.getClass(), "Index error");
                    //Log.info(this.getClass(),"RESPONSE: "+response);
                    error = true;
                }
            }
            //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 4 controllo condizioni per salvare indice - elemento "+el.getId()+" di tipo "+el.getTypeName());
            if (!error) {
                //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 5 salvo indice in DB- elemento "+el.getId()+" di tipo "+el.getTypeName());
                saveIdxStatus("fields", type, el.getId());
            } else {
                //VMAZZEO//Log.info(this.getClass(),"#### FIELD-INDEX 6 mancano condizioni per salvare indice ("+vals.size()+")- elemento "+el.getId()+" di tipo "+el.getTypeName());

            }
        }
        elkClient.close();
    }

    public void doFieldIndex(String type) throws AxmrGenericException, UnknownHostException {
        doFieldIndex(type, false);
    }

    public void doFieldIndex(String type, boolean forceAll) throws UnknownHostException, AxmrGenericException {
        Criteria c = docService.getDocDAO().getCriteria("main");
        Long typeId = docService.getTypeIdByNameOrId(type);
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(Restrictions.eq("type.id", typeId));
        if (!forceAll) {
            DetachedCriteria dateJoin = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub");
            dateJoin.add(Restrictions.eqProperty("sub.objId", "main.id"));
            dateJoin.add(Restrictions.eq("sub.indexName", "fields"));
            dateJoin.setProjection(Property.forName("sub.lastUpdateDt"));
            DetachedCriteria subCriteria = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub2");
            subCriteria.add(Restrictions.eq("sub2.indexName", "fields"));
            subCriteria.add(Restrictions.eq("sub2.objType", type));
            subCriteria.setProjection(Property.forName("sub2.objId"));
            c.add(
                    Restrictions.or(
                            Subqueries.propertyGe("main.lastUpdateDt", dateJoin),
                            Subqueries.propertyNotIn("main.id", subCriteria)
                    )
            );
        }
        List<Element> els = c.list();
        if (els != null) {
            for (Element el : els) {
                fieldIndex(el);
            }
        }
    }

    public void fullIndex(Long elId) throws UnknownHostException, AxmrGenericException {
        fullIndex(docService.getDocDAO().getById(elId));
    }

    public void fullIndex(Element el) throws UnknownHostException, AxmrGenericException {
        //Log.info(this.getClass()," - FULL-INDEX! - elemento "+el.getId()+" di tipo "+el.getTypeName()+" controllo se indicizzabile...");
        if (fullIndexObjsList.size() > 0 && !fullIndexObjsList.contains(el.getTypeName().toLowerCase())) {
            //Log.info(this.getClass()," - escludo indicizzazione full elemento "+el.getId()+" di tipo "+el.getTypeName());
            return;
        } else if (fullIndexObjsList.size() == 0 && !el.getType().isSearchable()) {
            //Log.info(this.getClass()," - escludo indicizzazione (isSearchable) full elemento "+el.getId()+" di tipo "+el.getTypeName());
            return;
        }
        //VMAZZEO//Log.info(this.getClass()," - - - elemento "+el.getId()+" di tipo "+el.getTypeName()+" indicizzo...");
        String type = el.getTypeName();
        Log.info(this.getClass(), " - Controllo che l'indice dell'elemento non sia stato aggiornato nel frattempo el:" + el.getId() + " di tipo " + el.getTypeName());
        isDao = new BaseDao<ElkIndexesStatus>(docService.getTxManager(), "doc", ElkIndexesStatus.class);
        Criteria c = isDao.getCriteria();
        c.add(Restrictions.eq("indexName", "full"))
                .add(Restrictions.eq("objType", type))
                .add(Restrictions.eq("instance", this.clusterName))
                .add(Restrictions.eq("objId", el.getId()));
        ElkIndexesStatus elIdx = (ElkIndexesStatus) c.uniqueResult();
        if (elIdx != null) {
            if (el.getLastUpdateDt() != null) {
                if (elIdx.getLastUpdateDt().after(el.getLastUpdateDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di ultima modifica el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            } else {
                if (elIdx.getLastUpdateDt().after(el.getCreationDt())) {
                    Log.info(this.getClass(), " -  - - Escludo in quanto data di incizzazione e successiva a data di creazione elemento non modificato el:" + el.getId() + " di tipo " + el.getTypeName());
                    return;
                }
            }
        }

        Log.info(this.getClass(),"#### FULL-INDEX! - elemento "+el.getId()+" di tipo "+el.getTypeName());
        Client elkClient = getNewClient();
        ElkSimpleElement tsel = new ElkSimpleElement();
        IndexRequest tindexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), el.getId() + "");
        tindexRequest.source(new Gson().toJson(tsel));
        IndexResponse tresponse = elkClient.index(tindexRequest).actionGet();
        Log.info(this.getClass(),"#### FULL-INDEX! - elemento "+el.getId()+" Risposta: "+tresponse.isCreated());

        //Log.info(this.getClass(),"PREPARE indice simple - tipo "+type.toLowerCase()+" - id: "+el.getId());
        Map<String, Object> maps = new HashMap<String, Object>();
        maps.put("date_detection", true);
        LinkedList<Object> templates = new LinkedList<Object>();
        Map<String, ElkTemplate> singleTemplate = new HashMap<String, ElkTemplate>();
        singleTemplate.put("noanafields",new ElkTemplate("*_NOTANALYZED","*", new ElkMapping("string","not_analyzed")));
        templates.add(singleTemplate);
        singleTemplate = new HashMap<String,ElkTemplate>();
        singleTemplate.put("codefields",new ElkTemplate("*_CODE","*", new ElkMapping("string","not_analyzed")));
        templates.add(singleTemplate);
        maps.put("dynamic_templates", templates);
        //Log.info(this.getClass(), new Gson().toJson(maps));

        PutMappingResponse putMappingResponse = elkClient.admin().indices()
                .preparePutMapping(indexPrefix.toLowerCase() + "-simple")
                .setType(type.toLowerCase())
                .setSource(new Gson().toJson(maps))
                .execute().actionGet();
        //Log.warn(this.getClass(), putMappingResponse.toString());


        //ElkFullElement tcel = new ElkFullElement();
        tindexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-full", type.toLowerCase(), el.getId() + ""); //"testEl"
        tindexRequest.source(new Gson().toJson(tsel));
        tresponse = elkClient.index(tindexRequest).actionGet();

        //Log.info(this.getClass(),"PREPARE indice full - tipo "+type.toLowerCase()+" - id: "+el.getId());
        putMappingResponse = elkClient.admin().indices()
                .preparePutMapping(indexPrefix.toLowerCase() + "-full")
                .setType(type.toLowerCase())
                .setSource(new Gson().toJson(maps))
                .execute().actionGet();
        //Log.warn(this.getClass(), putMappingResponse.toString());


        if (el.isDeleted()) {
            DeleteRequest deleterequest = new DeleteRequest(indexPrefix.toLowerCase() + "-full", type.toLowerCase(), el.getId() + "");
            DeleteResponse response = elkClient.delete(deleterequest).actionGet();
            deleterequest = new DeleteRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), el.getId() + "");
            response = elkClient.delete(deleterequest).actionGet();
            if (response != null && response.getShardInfo().getFailed() == 0) { // && response.isFound()) {
                saveIdxStatus("simple", type, el.getId());
                saveIdxStatus("full", type, el.getId());
            } else {
                //Index creation error
                Log.error(this.getClass(), "Index creation error");
                Log.error(this.getClass(), "RESPONSE: " + response);
            }
        } else {
            ElkSimpleElement sel = ElkSimpleElement.elementToSimple(el);
            /*
            Log.info(this.getClass(),"PREPARE indice simple - tipo "+type.toLowerCase()+" - id: "+el.getId());
            Log.info(this.getClass(),new Gson().toJson(sel.getMapping()));
            putMappingResponse = getClient().admin().indices()
                    .preparePutMapping(indexPrefix.toLowerCase() + "-simple")
                    .setType(type.toLowerCase())
                    .setSource(new Gson().toJson(sel.getMapping()))
                    .execute().actionGet();
            Log.warn(this.getClass(), putMappingResponse.toString());

            PutMappingRequest mappingRequest = new PutMappingRequest(indexPrefix.toLowerCase() + "-simple");
            Map<String, Object> properties = new HashMap<>();
            properties.put("properties", sel.getMapping());
            mappingRequest = mappingRequest.type(type).source(properties);
            putMappingResponse = getClient().admin().indices().putMapping(mappingRequest).actionGet();
            Log.warn(this.getClass(), putMappingResponse.toString());
            */

            /*
            PutMappingRequest mappingRequest = new PutMappingRequest(indexName);
            Map<String, Object> mappingsMap = (Map<String, Object>) gson.fromJson(gson.toJson(mapping), Json._obj_map_type);
             */

            //Log.info(this.getClass(),"PUT indice simple - tipo "+type.toLowerCase()+" - id: "+el.getId());
            IndexRequest indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), el.getId() + "");
            //IndexRequest indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase()).prep;
            //Log.info(this.getClass(),new GsonBuilder().excludeFieldsWithoutExposeAnnotation().create().toJson(sel));
            indexRequest.source(new Gson().toJson(sel));
            //indexRequest.source(new GsonBuilder().excludeFieldsWithoutExposeAnnotation().create().toJson(sel));
            IndexResponse response = elkClient.index(indexRequest).actionGet();
            ElkFullElement cel;
            if (fullIndexObjsList.size() > 0) {
                //Log.info(this.getClass()," - - Elemento "+el.getTypeName()+" lista elementi presente");
                cel = ElkFullElement.simpleToComplex(sel, el, true, fullIndexObjsList, fullIndexWithParentsObjsList);
            } else {
                //Log.info(this.getClass()," - - Elemento "+el.getTypeName()+" lista elementi NON presente");
                cel = ElkFullElement.simpleToComplex(sel, el, true, null, null);
            }
            /*
            Log.info(this.getClass(),"PREPARE indice full - tipo "+type.toLowerCase()+" - id: "+el.getId());
            Log.info(this.getClass(),new Gson().toJson(cel.getMapping()));
            putMappingResponse = getClient().admin().indices()
                    .preparePutMapping(indexPrefix.toLowerCase() + "-full")
                    .setType(type.toLowerCase())
                    .setSource(new Gson().toJson(cel.getMapping()))
                    .execute().actionGet();
            */
            //Log.info(this.getClass(),"PUT indice full - tipo "+type.toLowerCase()+" - id: "+el.getId());
            indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-full", type.toLowerCase(), el.getId() + "");
            indexRequest.source(new Gson().toJson(cel));
            //indexRequest.source(new GsonBuilder().excludeFieldsWithoutExposeAnnotation().create().toJson(cel));
            response = elkClient.index(indexRequest).actionGet();
            //Log.info(this.getClass(),"RESPONSE: "+response);
            if (cel.getChildren().size() > 0) {
                Iterator<String> it = cel.getChildren().keySet().iterator();
                while (it.hasNext()) {
                    String t = it.next();
                    for (int i = 0; i < cel.getChildren().get(t).size(); i++) {
                        recursiveFullIndex(cel.getChildren().get(t).get(i));
                    }
                }
            }
            if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {
                saveIdxStatus("simple", type, el.getId());
                saveIdxStatus("full", type, el.getId());
            } else {
                //Index creation error
                Log.error(this.getClass(), "Index creation error");
                Log.error(this.getClass(), "RESPONSE: " + response);

            }
        }
        elkClient.close();
    }

    public void recursiveFullIndex(ElkFullElement elk) throws AxmrGenericException, UnknownHostException {
        String type = elk.getType();
        Long id = elk.getId();
        IndexRequest indexRequest;
        Client elkClient = getNewClient();

        Map<String, Object> maps = new HashMap<String, Object>();
        maps.put("date_detection", true);
        LinkedList<Object> templates = new LinkedList<Object>();
        Map<String, ElkTemplate> singleTemplate = new HashMap<String, ElkTemplate>();
        singleTemplate.put("noanafields", new ElkTemplate("*_NOTANALYZED", "*", new ElkMapping("string", "not_analyzed")));
        templates.add(singleTemplate);
        singleTemplate = new HashMap<String,ElkTemplate>();
        singleTemplate.put("codefields",new ElkTemplate("*_CODE","*", new ElkMapping("string","not_analyzed")));
        templates.add(singleTemplate);
        maps.put("dynamic_templates", templates);
        //Log.info(this.getClass(), new Gson().toJson(maps));

        PutMappingResponse putMappingResponse = elkClient.admin().indices()
                .preparePutMapping(indexPrefix.toLowerCase() + "-full")
                .setType(type.toLowerCase())
                .setSource(new Gson().toJson(maps))
                .execute().actionGet();

        //Log.info(this.getClass(),"PUT indice full - tipo "+type.toLowerCase()+" - id: "+elk.getId());
        indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-full", type.toLowerCase(), elk.getId() + "");
        indexRequest.source(new Gson().toJson(elk));
        IndexResponse response = elkClient.index(indexRequest).actionGet();
        //Log.info(this.getClass(),"RESPONSE: "+response);
        Log.info(this.getClass(), "Processo figli da indicizzare");
        if (elk.getChildren().size() > 0) {
            Iterator<String> it = elk.getChildren().keySet().iterator();
            while (it.hasNext()) {
                String t = it.next();
                for (int i = 0; i < elk.getChildren().get(t).size(); i++) {
                    recursiveFullIndex(elk.getChildren().get(t).get(i));
                }
            }
        }
        if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {
        } else {
            //Index creation error
            Log.error(this.getClass(), "Index creation error");
            Log.error(this.getClass(), "RESPONSE: " + response);

        }

        putMappingResponse = elkClient.admin().indices()
                .preparePutMapping(indexPrefix.toLowerCase() + "-simple")
                .setType(type.toLowerCase())
                .setSource(new Gson().toJson(maps))
                .execute().actionGet();

        //Log.info(this.getClass(),"PUT indice simple - tipo "+type.toLowerCase()+" - id: "+elk.getId());
        indexRequest = new IndexRequest(indexPrefix.toLowerCase() + "-simple", type.toLowerCase(), elk.getId() + "");
        indexRequest.source(new Gson().toJson((ElkSimpleElement) elk));
        response = elkClient.index(indexRequest).actionGet();
        //Log.info(this.getClass(),"RESPONSE: "+response);
        if (response != null && response.getShardInfo().getFailed() == 0) { // && (response.isCreated() || !response.getIndex().isEmpty() || !response.getId().isEmpty())) {
            saveIdxStatus("simple", type, id);
            saveIdxStatus("full", type, id);
        } else {
            //Index creation failed
            Log.error(this.getClass(), "Index creation error");
            Log.error(this.getClass(), "RESPONSE: " + response);
        }
        elkClient.close();
    }


    public void doFullIndex(String type) throws AxmrGenericException, UnknownHostException {
        doFullIndex(type, false);
    }

    public void doFullIndex(String type, boolean forceAll) throws UnknownHostException, AxmrGenericException {
        Log.info(this.getClass(), "####DO FULL INDEX!!");
        Long typeId = docService.getTypeIdByNameOrId(type);
        Criteria c = docService.getDocDAO().getCriteria("main");
        c.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY)
                .add(Restrictions.eq("type.id", typeId));
        if (!forceAll) {
            DetachedCriteria dateJoin = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub");
            dateJoin.add(Restrictions.eq("sub.indexName", "full"));
            dateJoin.add(Restrictions.eq("sub.instance", this.clusterName));
            dateJoin.add(Restrictions.eqProperty("sub.objId", "main.id"));
            dateJoin.setProjection(Property.forName("sub.lastUpdateDt"));
            DetachedCriteria subCriteria = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub2");
            subCriteria.add(Restrictions.eq("sub2.indexName", "full"));
            subCriteria.add(Restrictions.eq("sub2.instance", this.clusterName));
            subCriteria.add(Restrictions.eq("sub2.objType", type));
            subCriteria.setProjection(Property.forName("sub2.objId"));
            c.add(
                    Restrictions.or(
                            Subqueries.propertyGe("main.lastUpdateDt", dateJoin),
                            Subqueries.propertyNotIn("main.id", subCriteria)
                    )
            );
        }
        List<Element> els = c.list();
        if (els != null) {
            for (Element el : els) {
                //Log.info(this.getClass()," - - ElkFullIndex - indicizzo elemento di tipo "+el.getType().getTypeId()+" - obj_id:"+el.getId());
                fullIndex(el);
            }
        }
    }

    public String getScopeFilter(IUser user) {
        String[] groups = new String[user.getAuthorities().size()];
        for (int i = 0; i < user.getAuthorities().size(); i++) {
            groups[i] = escape(((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase());
        }
        String scopeShould = "{\"match\" : { \"viewableByUsers\" : \"" + escape(user.getUsername().toLowerCase()) + "\"}},\n" +
                "           {\"wildcard\" : { \"viewableByUsers\": \"*\" }},\n" +
                "           {\"terms\" : { \"viewableByGroups\" : " + new Gson().toJson(groups) + " }}";
        scopeShould = "{\"terms\" : { \"viewableByUsers\" : [\"" + escape(user.getUsername().toLowerCase()) + "\", \"" + escape("all_users".toLowerCase()) + "\", \"*\"]}},\n" +
                "{\"terms\" : { \"viewableByGroups\" : " + new Gson().toJson(groups) + " }}";
        return "{\"should\": [\n" + scopeShould + "\n]}";
    }

    public String getScopeFilterFields(IUser user) {
        String[] groups = new String[user.getAuthorities().size()];
        for (int i = 0; i < user.getAuthorities().size(); i++) {
            groups[i] = escape(((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase());
        }

        String scopeFilter = "";

        scopeFilter = "{\"and\": [" +
                "{\"or\":[" +
                "   {\"terms\": {\"viewableByUsers\": [\"" + escape(user.getUsername().toLowerCase()) + "\",\"" + escape("all_users".toLowerCase()) + "\"]}}," +
                "   {\"terms\": {\"viewableByGroups\": " + new Gson().toJson(groups) + "}}" +
                "   ]" +
                "}," +
                "{\"or\":[" +
                "   {\"terms\": {\"objViewableByUsers\": [\"" + escape(user.getUsername().toLowerCase()) + "\",\"" + escape("all_users".toLowerCase()) + "\"]}}," +
                "   {\"terms\": {\"objViewableByGroups\": " + new Gson().toJson(groups) + "}}" +
                "   ]" +
                "}" +
                "]}";


        return scopeFilter;
        /*
        String scopeShould="{\"match\" : { \"viewableByUsers\" : \""+escape(user.getUsername().toLowerCase())+"\"}},\n"+
                "           {\"wildcard\" : { \"viewableByUsers\": \"*\" }},\n"+
                "           {\"terms\" : { \"viewableByGroups\" : "+new Gson().toJson(groups)+" }}";
        scopeShould="{\"terms\" : { \"viewableByUsers\" : [\""+escape(user.getUsername().toLowerCase())+"\", \""+escape("all_users".toLowerCase())+"\", \"*\"]}},\n"+
                "{\"terms\" : { \"viewableByGroups\" : "+new Gson().toJson(groups)+" }}";
        return "{\"should\": [\n"+scopeShould+"\n]}";
        */
    }

    public SearchResponse doElkQuery(IUser user, String indexType, String type, String filter, String sidx, String sord, int page, int rpp, boolean fields) throws UnknownHostException {
        String[] groups = new String[user.getAuthorities().size()];
        for (int i = 0; i < user.getAuthorities().size(); i++) {
            groups[i] = escape(((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase());
        }
        String scopedFilter = "{\"and\":[\n" +
                "          {\"bool\":" + getScopeFilter(user) + "},\n" +
                filter +
                "        ]}";
        int start = (page - 1) * rpp;
        Client elkClient = getNewClient();
        SearchRequestBuilder requestBuilder = elkClient.prepareSearch(indexPrefix.toLowerCase() + "-" + indexType.toLowerCase()).setTypes(type.toLowerCase()).setSearchType(SearchType.DEFAULT);
        SortOrder smod = SortOrder.DESC;
        if (sidx != null && !sidx.isEmpty()) {
            if (sord != null && !sord.isEmpty()) {
                if (sord.toLowerCase().equals("desc")) {
                    smod = SortOrder.DESC;
                } else {
                    smod = SortOrder.ASC;
                }
            }
        } else {
            sidx = "id";
        }
        requestBuilder.setPostFilter(scopedFilter).addSort(sidx, smod)
                .setFrom(start).setSize(rpp);
        if (!fields) requestBuilder.setNoFields();
        //VMAZZEO//Log.info(this.getClass(),requestBuilder.toString());
        SearchResponse response = requestBuilder.execute().actionGet();

        elkClient.close();
        return response;
    }

    public HashMap<String, List<Long>> getFilteredIds(IUser user, String indexType, String type, String filter, int page, int rpp, boolean fields) throws UnknownHostException {
        SearchResponse response = doElkQuery(user, indexType, type, filter, null, null, page, rpp, fields);
        List<Long> ids = new LinkedList<Long>();
        for (int i = 0; i < response.getHits().getTotalHits(); i++) {
            ids.add(Long.parseLong(response.getHits().getHits()[i].getId()));
        }
        List<Long> tots = new LinkedList<Long>();
        tots.add(response.getHits().getTotalHits());
        HashMap<String, List<Long>> ret = new HashMap<String, List<Long>>();
        ret.put("tot", tots);
        ret.put("ids", ids);
        return ret;
    }


    public void closeDocumentService() {
        globalTx.destroy();
    }

    public static String escape(String stringa) {
        return stringa.replaceAll("[-]*", "");
    }

    public List<FieldSearchResult> fullsearch(IUser user, String pattern) throws RestException {
        try {
            String[] groups = new String[user.getAuthorities().size()];
            for (int i = 0; i < user.getAuthorities().size(); i++) {
                groups[i] = escape(((List<IAuthority>) user.getAuthorities()).get(i).getAuthority().toLowerCase());
            }
            String query = "{\"query\":" +
                    "   {\"filtered\":" +
                    "       {\"query\":" +
                    "           {\"match\":" +
                    "               {\"stringValue\":\"" + pattern + "\"}" +
                    "           },\n" +
                    "       \"filter\":{" +
                    "           \"and\":[" + getScopeFilterFields(user) + "," +
                    "           {\"match\":" +
                    "               {\"stringValue\":\"" + pattern + "\"}" +
                    "           }" +
                    "           ]" +
                    "       }" +
                    "   }" +
                    "},\"sort\": [\n" +
                    "        { \"_score\": { \"order\": \"desc\" }}\n" +
                    "    ]" +
                    "}";
            Client elkClient = getNewClient();
            SearchRequestBuilder requestBuilder = elkClient.prepareSearch(indexPrefix.toLowerCase() + "-fields").setSearchType(SearchType.DEFAULT).setSource(query);
            //Log.info(getClass(), "Search " + indexPrefix + " ...");
            //Log.info(getClass(), "Search " + query + " ...");
            SearchResponse response = requestBuilder.execute().actionGet();
            elkClient.close();
            if (response.getHits().getTotalHits() > 0) {
                HashMap<Long, FieldSearchResult> ret = new HashMap<Long, FieldSearchResult>();
                List<Long> orderedIds = new LinkedList<Long>();
                List<FieldSearchResult> results = new LinkedList<FieldSearchResult>();
                for (int i = 0; i < response.getHits().getHits().length; i++) {
                    SearchHit sr = response.getHits().getHits()[i];
                    ElkValue elk = new Gson().fromJson(sr.getSourceAsString(), ElkValue.class);
                    FieldSearchResult fsr = FieldSearchResult.buildFromElkValue(elk, sr.getScore());
                    if (ret.containsKey(fsr.getObjId())) {
                        fsr = ret.get(fsr.getObjId());
                        fsr.fromElkValue(elk, sr.getScore());
                        ret.put(fsr.getObjId(), fsr);
                    } else {
                        orderedIds.add(fsr.getObjId());
                        ret.put(fsr.getObjId(), fsr);
                    }
                }
                for (Long id : orderedIds) {
                    results.add(ret.get(id));
                }
                return results;
            } else return new LinkedList<FieldSearchResult>();

        } catch (UnknownHostException e) {
            throw new RestException(e.getMessage(), 1);
        }


    }


    public List<ElkIdxStatus> IdxStatusesBlocco() {
        String txName = "doc";
        isDao = new BaseDao<ElkIndexesStatus>(docService.getTxManager(), txName, ElkIndexesStatus.class);
        Criteria c = isDao.getCriteria("main");
        ProjectionList properties = Projections.projectionList();
        properties.add(Projections.groupProperty("indexName"));
        properties.add(Projections.groupProperty("objType"));
        properties.add(Projections.count("objId"), "indexed");
        properties.add(Projections.max("lastUpdateDt"), "lastUpdateDt");
        c.add(Restrictions.eq("instance", this.clusterName));
        c.setProjection(properties);
        List<Object[]> res = c.list();
        List<ElkIdxStatus> ret = new LinkedList<ElkIdxStatus>();
        for (int i = 0; i < res.size(); i++) {
            String indexName = (String) res.get(i)[0];
            String objType = (String) res.get(i)[1];
            Long indexed = (Long) res.get(i)[2];
            GregorianCalendar lastIdxDt = (GregorianCalendar) res.get(i)[3];
            ElkIdxStatus sts = new ElkIdxStatus();
            sts.setIdxName(indexName);
            sts.setObjType(objType);
            sts.setIndexed(indexed);
            sts.setLastUpdateDt(lastIdxDt);
            ret.add(sts);
        }
        for (int i = 0; i < ret.size(); i++) {
            String objType = ret.get(i).getObjType();
            String idxName = ret.get(i).getIdxName();
            Long typeId = docService.getTypeIdByNameOrId(objType);

            Criteria c1 = docService.getDocDAO().getCriteria("main");
            c1.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY).add(Restrictions.eq("type.id", typeId)).add(Restrictions.eq("deleted", false));
            Criteria c2 = docService.getDocDAO().getCriteria("main");
            c2.setResultTransformer(Criteria.DISTINCT_ROOT_ENTITY).add(Restrictions.eq("type.id", typeId)).add(Restrictions.eq("deleted", false));

            DetachedCriteria dateJoin = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub");
            dateJoin.add(Restrictions.eq("sub.indexName", idxName));
            dateJoin.add(Restrictions.eqProperty("sub.objId", "main.id"));
            dateJoin.setProjection(Property.forName("sub.lastUpdateDt"));
            DetachedCriteria subCriteria = DetachedCriteria.forClass(ElkIndexesStatus.class, "sub2");
            subCriteria.add(Restrictions.eq("sub2.indexName", idxName));
            subCriteria.add(Restrictions.eq("sub2.objType", objType));
            subCriteria.setProjection(Property.forName("sub2.objId"));
            /*
            c.add(
                Restrictions.or(
                    Subqueries.propertyGe("main.lastUpdateDt",dateJoin),
                    Subqueries.propertyNotIn("main.id", subCriteria)
                )
            );
            */
            c1.add(Subqueries.propertyGe("main.lastUpdateDt", dateJoin));
            c2.add(Subqueries.propertyNotIn("main.id", subCriteria));
            ret.get(i).setToBeUpdated((Long) c1.setProjection(Projections.rowCount()).uniqueResult());
            ret.get(i).setMissing((Long) c2.setProjection(Projections.rowCount()).uniqueResult());
        }
        return ret;
    }

    public List<ElkIdxStatus> IdxStatuses() {
        List<ElkIdxStatus> ret = new LinkedList<ElkIdxStatus>();
        String sqlQuery = "SELECT name, objtype, num_indexed, num_update, num_missing FROM ELK_IDX_STATUSVIEW";
        SQLQuery query = docService.getAxmr3txManager().getSession("doc").createSQLQuery(sqlQuery);
        List<Object[]> rows = query.list();
        for (Object[] row : rows) {
            ElkIdxStatus sts = new ElkIdxStatus();
            sts.setIdxName(row[0].toString());
            sts.setObjType(row[1].toString());
            sts.setIndexed(Long.parseLong(row[2].toString()));
            sts.setToBeUpdated(Long.parseLong(row[3].toString()));
            sts.setMissing(Long.parseLong(row[4].toString()));
            ret.add(sts);
        }
        return ret;
    }

}

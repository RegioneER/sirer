<?

// Menu principale

if(strtoupper($testo_config['language'])=="EN"||!isset($testo_config['language'])){
	$testo_config['Help_tab_0']='<b>Private portal home page: </b><br>From the private portal homepage, the user has a general 
overview of the status of his working groups. The page resumes recently posted meetings, to-be published meetings, document areas and forum available';
	$testo_config['Help_tab_1']='<b>Meetings & Events: </b><br>The calendar is a powerful tool for managing group 
appointments and the availability of project participants. The calendar is browseable by day, week and month.  
From here it is possible to create new events';
	$testo_config['Help_tab_1_day']='<b>Calendar in day view:</b><br> It is possible to browse the calendar also in week, month and year view';
	$testo_config['Help_tab_1_week']='<b>Calendar in week view:</b><br> It is possible to browse the calendar also in day, month and year view';
	$testo_config['Help_tab_1_month']='<b>Calendar in month view:</b><br> It is possible to browse the calendar also in day, week and year view';
	$testo_config['Help_tab_1_year']='<b>Calendar in year view:</b><br> It is possible to browse the calendar also in day, week and month view';
	$testo_config['Help_tab_1_new_riunione']='<b>New Event creation:</b><br> To create an event it is necessary to input 
event date&time details and event name.  Other additional information (Description, location) are optional. 
By clicking on the button below \'Create Event\' it is possible to proceed to the meeting definition';
	$testo_config['Help_tab_1_users']='<b>Step 1 of 5- Meeting creation: select meeting participants: </b><br> In this form you enter all resources 
that you want to book for the appointment.  Once selected,  you can move on to the next step (Availability)';
	$testo_config['Help_tab_1_check']='<b>Step 2 of 5 - Meeting creation: participants availability </b><br>  On this page 
it is possible to check participants availability, depending on the selection done in the previous step. 
Then you can move on to the next step (Attach documents)';
	$testo_config['Help_tab_1_allegati']='<b>Step 3 of 5 - Meeting creation: attach documents</b><br> On this page 
it is possible to insert documents in the meeting invitation.  Then you can move on to the next step (Agenda)';
	$testo_config['Help_tab_1_odg']='Step 4 of 5 - Meeting creation: insert an event agenda</b><br> On this page 
it is possible to write or paste on the editor a meeting agenda.  Then you can move on to the next step (Preview)';
	$testo_config['Help_tab_1_preview']='Step 5 of 5 - Meeting creation: preview</b><br> On this page 
it is possible to check a summary of the meeting details. Then you can publish it by clicking the button at the bottom of the summary.';
	$testo_config['Help_tab_3']='<b>Document Areas List: </b><br> On this page you can access to the active document areas. Team administrators can even create new ones.';
	$testo_config['Help_tab_3_id_area']='<b>Document publishing: </b><br> On this page you can upload documents that 
you want to grant other users to access and download documents other users have saved in the different document areas. 
You can also use a version control for the documents.';
	$testo_config['Help_tab_13']='<b> Forum List: </b><br>On this page you can access to the active forum. Team administrators can even create new ones.';
	$testo_config['Help_tab_13_id_forum']='<b> Forum List: </b><br>A forum is a place for discussions on specific subjects. 
Every discussion is divided into discussion threads. 
The forum part of the platform is particularly suited as a communication platform.';
	$testo_config['Help_tab_12']='<b> Messaggistica Privata </b><br>In questa sezione è possibile inviare messaggi privati agli altri utenti della piattaforma.';
	$testo_config['Help_tab_15']='<b>Administration Tool: </b><br> Group coordinators can create and add users to the workgroups. Users can view the project structure and teams composition';
	$testo_config['Help_tab_4']='<b>Contacts: </b><br> Complete contact details of all the project participants.   	
 Here you can also change or complete your personal details. ';
}
else if(strtoupper($testo_config['language'])=="IT"){
	/*$testo_config['Help_tab_0']='<b>Private portal home page: </b><br>From the private portal homepage, the user has a general 
overview of the status of his working groups. The page resumes recently posted meetings, to-be published meetings, document areas and forum available';*/

$testo_config['Help_tab_0']='<b>Home page personale: </b><br>Dalla home page personale, l\'utente ha una visione generale della situazione dei suoi gruppi di lavoro.
 La pagina riassume le prossime riunioni, le riunioni in attesa di pubblicazione, le aree documentali e i forum disponibili';


// Calendario

/*$testo_config['Help_tab_1']='<b>Meetings & Events: </b><br>The calendar is a powerful tool for managing group 
appointments and the availability of project participants. The calendar is browseable by day, week, month and year.  
From here it is possible to create new events';*/
$testo_config['Help_tab_1']='<b>Riunioni: </b><br>Il calendario è un potente strumento per amministrare le riunioni 
dei gruppi e la disponibilità dei partecipanti al progetto. Il calendario è navigabile per giorno, settimana, mese e anno. 
Da qui è possibile creare nuove riunioni.';
//$testo_config['Help_tab_1_day']='<b>Calendar in day view:</b><br> It is possible to browse the calendar also in week, month and year view';
$testo_config['Help_tab_1_day']='<b>Calendario in visione giornaliera:</b><br> E\' possibile navigare il calendario anche in visione settimanale, mensile e annuale.';
//$testo_config['Help_tab_1_week']='<b>Calendar in week view:</b><br> It is possible to browse the calendar also in day, month and year view';
$testo_config['Help_tab_1_week']='<b>Calendario in visione settimanale:</b><br> E\' possibile navigare il calendario anche in visione giornaliera, mensile e annuale.';
//$testo_config['Help_tab_1_month']='<b>Calendar in month view:</b><br> It is possible to browse the calendar also in day, week and year view';
$testo_config['Help_tab_1_month']='<b>Calendario in visione mensile:</b><br> E\' possibile navigare il calendario anche in visione giornaliera, settimanale e annuale.';
//$testo_config['Help_tab_1_year']='<b>Calendar in year view:</b><br> It is possible to browse the calendar also in day, week and month view';
$testo_config['Help_tab_1_year']='<b>Calendario in visione annuale:</b><br> E\' possibile navigare il calendario anche in visione giornaliera, settimanale e mensile.';

/*$testo_config['Help_tab_1_new_riunione']='<b>New Event creation:</b><br> To create an event it is necessary to input 
event date&time details and event name.  Other additional information (Description, location) are optional. 
By clicking on the button below \'Create Event\' it is possible to proceed to the meeting definition';*/
$testo_config['Help_tab_1_new_riunione']='<b>Creazione di una nuova riunione:</b><br> Per creare una riunione è necessario inserire
la data, l\'ora, i dettagli e il nome della riunione.  Le restanti informazioni, quali la descrizione e il luogo della riunione, sono facoltative. 
Cliccando il pulsante sottostante \'Crea un evento\' è possibile procedere alla creazione dell\'evento';
/*$testo_config['Help_tab_1_users']='<b>Step 1 of 5- Meeting creation: select meeting participants: </b><br> In this form you enter all resources 
that you want to book for the appointment.  Once selected,  you can move on to the next step (Availability)';*/
$testo_config['Help_tab_1_users']='<b>Step 1 di 5- Creazione della riunione: seleziona i partecipanti alla riunione: </b><br> In questa sezione bisogna inserire tutte 
le persone che si vuole invitare alla riunione.  Una volta fatta la selezione, potete passare allo step successivo.';
/*$testo_config['Help_tab_1_check']='<b>Step 2 of 5 - Meeting creation: participants availability </b><br>  On this page 
it is possible to check participants availability, depending on the selection done in the previous step. 
Then you can move on to the next step (Attach documents)';*/
$testo_config['Help_tab_1_check']='<b>Step 2 di 5 - Creazione della riunione: disponibilità dei partecipanti </b><br>  In questa sezione è possibile
controllare la disponibilità dei partecipanti, selezionati nello step precendente. 
Fatto ciò potete passare allo step successivo.';
$testo_config['Help_tab_1_allegati']='<b>Step 3 di 5 - Creazione della riunione: documenti allegati</b><br> In questa sezione è possibile
 allegare documenti ai dettagli della riunione.  Fatto ciò potete passare allo step successivo.';
/*$testo_config['Help_tab_1_odg']='Step 4 of 5 - Meeting creation: insert an event agenda</b><br> On this page 
it is possible to write or paste on the editor a meeting agenda.  Once done, you can publish the event and send meeting invitations ';*/
$testo_config['Help_tab_1_odg']='Step 4 di 5 - Creazione della riunione: ordine del giorno</b><br> In questa sezione è possibile 
scrivere o incollare nell\'editor l\'ordine del giorno della riunione. Fatto ciò potete passare allo step successivo.';
/*$testo_config['Help_tab_1_preview']='Step 5 of 5 - Meeting creation: preview</b><br> On this page 
it is possible to check a summary of the meeting details. Then you can publish it by clicking the button at the bottom of the summary.';*/
$testo_config['Help_tab_1_preview']='Step 5 di 5 - Creazione della riunione: anteprima</b><br> In questa sezione è possibile 
controllare un riassunto dei dettagli della riunione. Fatto ciò potete pubblicare la riunione cliccando il pulsante in fondo al riassunto.';
//ALC
//$testo_config['Help_tab_3']='<b>Document Areas List: </b><br> On this page you can access to the active document areas. Team administrators can even create new ones.';
$testo_config['Help_tab_3']='<b>Lista delle Aree Documentali: </b><br> In questa sezione è possibile accedere alle aree documentali disponibili. I coordinatori dei gruppi possono anche crearne di nuove.';
/*$testo_config['Help_tab_3_id_area']='<b>Document publishing: </b><br> On this page you can upload documents that 
you want to grant other users to access and download documents other users have saved in the different document areas. 
You can also use a version control for the documents.';*/
$testo_config['Help_tab_3_id_area']='<b>Pubblicazione di un documento: </b><br> In questa sezione è possibile caricare documenti che
vuoi condividere con gli altri utenti dell\'area e scaricare i documenti caricati da altri utenti. 
E\' possible caricare anche versioni diverse di uno stesso documento.';

//Forum
//$testo_config['Help_tab_13']='<b> Forum List: </b><br>On this page you can access to the active forum. Team administrators can even create new ones.';
$testo_config['Help_tab_13']='<b> Lista dei forum: </b><br>In questa sezione è possibile accedere ai forum disponibili. I coordinatori dei gruppi possono anche crearne di nuovi.';
/*$testo_config['Help_tab_13_id_forum']='<b> Forum List: </b><br>A forum is a place for discussions on specific subjects. 
Every discussion is divided into discussion threads. 
The forum part of the platform is particularly suited as a communication platform.';*/
$testo_config['Help_tab_13_id_forum']='<b> Forum: </b><br>Un forum è il luogo per discutere di argomenti specifici.
Ogni nuovo topic individua un argomento di discussione specifico.
Il forum è particolarmente indicato come piattaforma di comunicazione e condivisione d\'informazioni all\'interno di un gruppo di lavoro.';

//$testo_config['Help_tab_12']='<b> Private Messenger </b><br>On this page you can send messages to other users';
$testo_config['Help_tab_12']='<b> Messaggistica Privata </b><br>In questa sezione è possibile inviare messaggi privati agli altri utenti della piattaforma.';

// Administration tool

//$testo_config['Help_tab_15']='<b>Administration Tool: </b><br> Group coordinators can create and add users to the workgroups. Users can view the project structure and teams composition';
$testo_config['Help_tab_15']='<b>Strumenti amministrativi: </b><br> I coordinatori di gruppo possono creare nuovi gruppi di lavoro e aggiungere utenti a quelli esistenti. Gli altri utenti possono vedere la struttura e composizione dei gruppi';

// Contacts


/*$testo_config['Help_tab_4']='<b>Contacts: </b><br> Complete contact details of all the project participants.   	
 Here you can also change or complete your personal details. ';*/
$testo_config['Help_tab_4']='<b>Contatti: </b><br> In questa sezione è possibile accedere ai dettagli di tutti gli utenti della piattaforma.   	
 E\' inoltre possibile aggiornare i dettagli personali. ';
}




?>
#!/usr/local/bin/perl   

############################################################
# 
#
#                       Driver Ianus
#			Version: 1.0.0
#
#
# Carlo Contino
#
# Modulo per effettuare il controllo all'accesso 
# degli Script Perl
# 
# 
############################################################

# MAIN



use DBI;

use LWP::Simple;

require "cgi-lib_pl.pl";

$INC[++$#INC]="/http/lib/DriverIanus";

$ENV{'REMOTE_USER'}=$ENV{'REMOTE_USERID'};
$ENV{'ID_PRINC_SERV'}=$ENV{'REMOTE_USERID'};

$ENV{'REMOTE_USER'}=~ s/\@(.*?)$//;
$ENV{'ID_PRINC_SERV'}=~ s/(.*)\@//;


$ENV{'ORACLE_HOME'}='/oracle/app/oracle/product/11.1.0/client';

$ENV{'TNS_ADMIN'}='/oracle/app/oracle/product/11.1.0/client/network/admin';


$ENV{HTMLDOC_NOCGI}=1;

$dir_root = $dir_config = $dir_cgi = $ENV{'DOCUMENT_ROOT'};
$dir_root =~ s/html$//;
$dir_cgi =~ s/html$/cgi/;
$dir_config =~ s/html$/config/;

$0=$ENV{'REQUEST_URI'};


$0 =~ s/download\//download?NOME_FILE=/;

$0 =~ s/\?(.*)//;


$http="http://".$ENV{'SERVER_NAME'}."/DriverIanus/monitor.inc.php?URI=".$0."&";




if ($ENV{'SERVER_PORT'} eq '443'){
	$http.="HTTPS=on&";
}

if ($ENV{'REMOTE_USER'} ne ''){
	use DBI;
	
	
	
	$ConfigFile = $dir_config . "/amministrazione.cfg";

if (open(CONFIG, $ConfigFile)) {
    while (<CONFIG>) {
	chop;
	$Vars[++$#Vars] = $_;
    }
    foreach $i (0 .. $#Vars) {
	if (substr($Vars[$i],0,1) ne '#') {
	   ($Name,$Value) = split(' ', $Vars[$i], 9999);
	   $ConfigVars{$Name} = $Value;
	}
    }
    close(CONFIG);
    $user_oracle = $ConfigVars{'OraUserid'} . "\@" . $ConfigVars{'OraInstance'};
    $password_oracle = $ConfigVars{'OraPassword'} ;
}
	$drh = DBI->install_driver( 'Oracle' );
	$dbh = $drh->connect('',$user_oracle,$password_oracle);
	#SSO
	$drh = DBI->install_driver( 'Oracle' );
		$dbh = $drh->connect('',$user_oracle,$password_oracle);
		$sql_query="select count(*) from idp_servizi where upper(url)=upper('$ENV{'SERVER_NAME'}') and ID=$ENV{'ID_PRINC_SERV'}";
		#$sql_query="select count(*) from user_objects where OBJECT_NAME ='IDP_UTENTI_SERVIZI'";
		$cursor=$dbh->prepare($sql_query);
		$cursor->execute;
		@result = $cursor->fetchrow_array();
		if ($result[0] eq '0'){
			$sql_query="select count(*) from user_objects where OBJECT_NAME ='IDP_UTENTI_SERVIZI'";
			$cursor=$dbh->prepare($sql_query);
			$cursor->execute;
			@result = $cursor->fetchrow_array();
			if ($result[0] eq '1'){
				$sql_query="select USERID_DEST, ID_SERV from IDP_UTENTI_SERVIZI where ID_SERV=(select ID from idp_servizi where upper(url)=upper('$ENV{'SERVER_NAME'}')) and userid='$ENV{'REMOTE_USER'}' and ID_PRINC_SERV=$ENV{'ID_PRINC_SERV'}";
				$cursor=$dbh->prepare($sql_query);
				$cursor->execute;
				if (@result = $cursor->fetchrow_array()){
					$ENV{'REMOTE_USER'}=$result[0];
					$ENV{'ID_PRINC_SERV'}=$result[1];
				}else {
					$sql_query="select USERID, ID_PRINC_SERV from IDP_UTENTI_SERVIZI where ID_PRINC_SERV=(select ID from idp_servizi where upper(url)=upper('$ENV{'SERVER_NAME'}')) and userid_dest='$ENV{'REMOTE_USER'}' and ID_SERV=$ENV{'ID_PRINC_SERV'}";
					$cursor=$dbh->prepare($sql_query);
					$cursor->execute;
					@result = $cursor->fetchrow_array();
					$ENV{'REMOTE_USER'}=$result[0];
					$ENV{'ID_PRINC_SERV'}=$result[1];
				}
				$sql_query="select ID_GRUPPOU from utenti_gruppiu where userid='$ENV{'REMOTE_USER'}'";
					$cursor=$dbh->prepare($sql_query);
				$cursor->execute;
				while (@result = $cursor->fetchrow_array()){
					$gruppi.="$ENV{'ID_PRINC_SERV'}.$result[0]|";
				}
				if ($gruppi!='') {
					$gruppi="|".$gruppi;
				}
				$ENV{'GRUPPI'}=$gruppi;
			}
			$http.="USERID=$ENV{'REMOTE_USER'}&GRUPPI=$ENV{'GRUPPI'}";
		}
		
	#FINE SSO
	$sql_query="select count(*) from user_tables where TABLE_NAME in ('SHIBFORCEUSER','SUPERSHIBUSERS')";
	$cursor=$dbh->prepare($sql_query);
	$cursor->execute;
	@result = $cursor->fetchrow_array();
	if ($result[0] eq '2'){
		$sql_query="select count(*) from SUPERSHIBUSERS where userid='$ENV{'REMOTE_USER'}'";
		$cursor=$dbh->prepare($sql_query);
		$cursor->execute;
		@result = $cursor->fetchrow_array();
		if ($result[0] eq '1'){
			$sql_query="select USERID_FORCED from SHIBFORCEUSER where USERID='$ENV{'REMOTE_USER'}'";
			$cursor=$dbh->prepare($sql_query);
			$cursor->execute;
			@result = $cursor->fetchrow_array();
			$ENV{'REMOTE_USER'}=$result[0];
			
			$sql_query="select ID_GRUPPOU from utenti_gruppiu where userid='$ENV{'REMOTE_USER'}'";
				$cursor=$dbh->prepare($sql_query);
			$cursor->execute;
			while (@result = $cursor->fetchrow_array()){
				$gruppi.="$ENV{'ID_PRINC_SERV'}.$result[0]|";
			}
			if ($gruppi!='') {
				$gruppi="|".$gruppi;
			}
			$ENV{'GRUPPI'}=$gruppi;
				
			
			
		}
	} 
	$http.="USERID=$ENV{'REMOTE_USER'}&GRUPPI=$ENV{'GRUPPI'}";
}

my $content = get $http;

if ($content eq 'REDIRECT'){
	print STDOUT &PrintHeader();
	$https_link="https://".$ENV{'SERVER_NAME'}."".$ENV{'REQUEST_URI'};
	print "<html><head><meta http-equiv='refresh' content='0;url=$https_link'></head></html>";
	exit(1);
}

if ($content eq 'FORBIDDEN'){
	print STDOUT &PrintHeader();	
	print "Utente non abilitato all'accesso";
	exit(1);
}

if ($content eq 'OK') 
{


$0 =~ s/\?(.*)$//;

$scriptname=$0;
$scriptname=~ s/\/cgi-bin//;


$file="$dir_cgi$scriptname";

$0=$file;


$ENV{SCRIPT_NAME}="/cgi-bin$scriptname";
$ENV{SCRIPT_FILENAME}=$file;


chdir $dir_cgi;

#chdir $dir_cgi;
use CGI qw(:standard);

if (!(-e $file)) {
	#print &PrintHeader();
  @split_1=split(/\//,$ENV{SCRIPT_NAME});
	@split=split(/\//, $file);
	#print "<li>$#split</li>";
	$i=1;
	foreach (@split) {
		if ($i<=$#split){
		$file_new.="/$_";
		#print "<li>$_</li>";
		}
		$i++;
	}
	if (-e $file_new) {
	$DRIVER_IANUS_SHIB_DOWNLOAD_FILENAME=$split[$#split];
	#print header( -type       => 'application/x-download', -attachment => $split[$#split], );
	$file=$file_new;
	$i=1;
	$script='';
	
  	foreach (@split_1) {
  		
		if ($i<$#split_1){
		$script.="/$split_1[$i]";
		#print "<li>$split_1[$i]</li>";
		}
		$i++;
	}
	
	
	#$script=$ENV{HTTP_HOST}.$script;
	print redirect ( -URL => "$script?$ENV{QUERY_STRING}&file_download=$split[$#split]");	
  exit;

	}
	else {
		print &PrintHeader();
		print "<hr>Errore: Script $file inesistente!!!<hr>";
		exit(0);
	}
}
else{
	$curr_dir= $ENV{'SCRIPT_FILENAME'};
	$curr_dir =~ s/\/?.[^\/]*$//g;
	#print STDOUT &PrintHeader();
	#print "$curr_dir";
	chdir $curr_dir;
}
if ($scriptname eq '/ammin_chpwd'){
	print redirect ( -URL => "/change_password");	
	exit(0);
}

unless ($return = do $file) {
		print &PrintHeader();
		print "<hr>Errore: <hr>";
		warn "couldn't parse $file: $@ " if $@;
	    print "couldn't parse $file: $@ " if $@;
	    warn "couldn't do $file: $!"    unless defined $return;
	    print "couldn't do $file: $!"    unless defined $return;
	    warn "couldn't run $file"       unless $return;
	    print "couldn't run $file"       unless $return;
	}
}
exit(0);

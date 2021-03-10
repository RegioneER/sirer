<?php 
if (isset($_GET['clearProfileData'])){
	system("rm -f ".$_SERVER['DOCUMENT_ROOT'].'/../xdebug-profile-logs/*');
	header("location: index.php");
	die();
}
$dir    = $_SERVER['DOCUMENT_ROOT'].'/../xdebug-profile-logs/';
$files1 = scandir($dir);

foreach ($files1 as $key=>$val){
	if (!preg_match("!\.log!", $val)) continue;
	$part1=str_replace("cachegrind.out.", "", $val);
	$part1=str_replace(".log", "", $part1);
	$parts=explode("-", $part1);
	$prog=$parts[1]-0;
	$listFiles.="<li>PID: {$parts[0]}, Progressivo Query: {$prog}, Tempo di esecuzione (sec): {$parts[2]}</li>";
	$content=file_get_contents($dir.$val);
	$listFiles.=nl2br($content);
	$pids[$parts[0]]=true;
	$querys[$parts[0]][$prog]["TS"]=$parts[2];
	$querys[$parts[0]][$prog]["CONTENT"]=nl2br($content);
}
$out=file_get_contents("container.html");
$pidOptions.="<option>Seleziona il pid</option>";
foreach ($pids as $key=>$val){
	if ($_GET['pid']==$key) $selected="selected";
	else $selected="";
	$pidOptions.="<option $selected value=\"$key\">$key</option>";
}

$out=str_replace("<!--pidOptions-->", $pidOptions, $out);
$title="Sql Profiler";
$out=str_replace("<!--title-->", $title, $out);

$table='<a class="btn btn-success" href="index.php?clearProfileData">Pulisci dati di profile</a>
		<div class="row">
									<div class="col-xs-12">
										<h3 class="header smaller lighter blue">SQL Queries</h3>

										<div class="clearfix">
											<div class="pull-right tableTools-container"></div>
										</div>

										<!-- div.table-responsive -->

										<!-- div.dataTables_borderWrap -->
										<div>
											<table id="dynamic-table" class="table table-striped table-bordered table-hover">
												<thead>
													<tr>
														<th>PID</th>
														<th>Query n.ro</th>
														<th>
															<i class="ace-icon fa fa-clock-o bigger-110"></i>
															Time Spent
														</th>
														<th>Content</th>
													</tr>
												</thead>
												<tbody>
		';
foreach ($pids as $pid=>$v){
	if (isset($_GET['pid']) && $_GET['pid']!=$pid) continue;
	foreach ($querys[$pid] as $key=>$val){
		$table.='
														<tr>
															<td>
																'.$pid.'
															</td>
															<td>'.$key.'</td>
															<td>'.$val['TS'].'</td>
	
															<td>
																'.$val['CONTENT'].'
															</td>
	
															
														</tr>
				';
	}
}

$table.='
												</tbody>
											</table>
										</div>
									</div>
								</div>
														
		
		
		';

$out=str_replace("<!--main-->", $table, $out);


die($out);

?>
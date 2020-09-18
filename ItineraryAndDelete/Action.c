Action()
{
	int random;
	int flights_count;
	char flight_index[50];
	char selected_flight_id[50];
	
	lr_start_transaction("UC_1_Itinerary_and_delete");
	
		lr_start_transaction("connect");
	
			web_add_auto_header("DNT", 
				"1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
		/*Correlation comment: Automatic rules - Do not change!  
		Original value='129609.063345484zzzzHzzpVQfiDDDDtAAAApfQHVHf' 
		Name ='userSession' 
		Type ='Rule' 
		AppName ='WebTours' 
		RuleName ='UserSession'*/
			web_reg_save_param_attrib(
				"ParamName=userSession",
				"TagName=input",
				"Extract=value",
				"Name=userSession",
				"Type=hidden",
				SEARCH_FILTERS,
				"RequestUrl=*/nav.pl*",
				LAST);
		
			web_url("WebTours", 
				"URL=http://localhost:1080/WebTours", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=", 
				"Snapshot=t1.inf", 
				"Mode=HTML", 
				LAST);		
		
			web_set_sockets_option("SSL_VERSION", "AUTO");
		
			web_websocket_send("ID=0", 
				"Buffer={\"messageType\":\"hello\",\"broadcasts\":{\"remote-settings/monitor_changes\":\"\\\"1599847578511\\\"\"},\"use_webpush\":true,\"uaid\":\"ddaed336ef8242e789f503edeab84ad5\"}", 
				"IsBinary=0", 
				LAST);
			
		lr_end_transaction("connect", LR_AUTO);
	
		/*Connection ID 0 received buffer WebSocketReceive0*/
	
		lr_start_transaction("login");
	
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(39);
			
			web_reg_find("Fail=NotFound",
				"Text=User password was correct",
				LAST);
		
			web_submit_data("login.pl",
				"Action=http://localhost:1080/cgi-bin/login.pl",
				"Method=POST",
				"TargetFrame=body",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
				"Snapshot=t2.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=userSession", "Value={userSession}", ENDITEM,
				"Name=username", "Value={login}", ENDITEM,
				"Name=password", "Value={password}", ENDITEM,
				"Name=login.x", "Value=41", ENDITEM,
				"Name=login.y", "Value=12", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
	
		lr_end_transaction("login",LR_AUTO);
	
		lr_start_transaction("itinerary");
	
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(15);
			
			web_reg_find("Fail=NotFound",
			"Text= User wants the intineraries",
			LAST);
			
			web_reg_save_param("flight_id",         
				"LB=<input type=\"hidden\" name=\"flightID\" value=\"",
				"RB=\"  />",
				"Ord=ALL",
				LAST);
	
			web_url("Itinerary Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("itinerary",LR_AUTO);
		
		flights_count = atoi(lr_eval_string("{flight_id_count}"));
		
		random = (flights_count == 1) ? 1 : rand()%(flights_count - 1) + 1;
		
		sprintf(flight_index, "%d", random);
		lr_save_string(lr_eval_string(flight_index), "flight_index");
		
		sprintf(selected_flight_id, "{flight_id_%d}", random);
		lr_save_string(lr_eval_string(selected_flight_id), "selected_flight_id");
	
		lr_start_transaction("delete");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(24);
			
			web_reg_find("Fail=Found",
			    "Text={selected_flight_id}",
				LAST);
	
			web_submit_form("Cancel Button", 
				ITEMDATA, 
				"Name={flight_index}", "Value=on", ENDITEM,  
				"Name=removeFlights.x", "Value=59", ENDITEM, 
				"Name=removeFlights.y", "Value=12", ENDITEM, 
				EXTRARES,
				"URL=http://localhost:1080/cgi-bin/itinerary.pl",
				"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
				ENDITEM,
				LAST);
		
		lr_end_transaction("delete",LR_AUTO);
	
		lr_think_time(18);
	
		lr_start_transaction("logout");
		
			web_reg_find("Fail=NotFound",
			"Text=Username",
			LAST);
	
			web_url("SignOff Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC_1_Itinerary_and_delete",LR_AUTO);

	return 0;
}
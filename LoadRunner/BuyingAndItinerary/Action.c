Action()
{
	int random;
	char flight_time[50];
	char flight_id[50];
	char outbound_flight[50];
	
	lr_start_transaction("UC_5_Buying_And_Itinerary");
	
		lr_start_transaction("connect");
	
			web_add_auto_header("DNT", 
				"1");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			web_reg_find("Fail=NotFound",
			"Text=The document has moved",
			LAST);

		/*Correlation comment: Automatic rules - Do not change!  
		Original value='129609.170595383zzzzHHVpHVcftAAAApzDAcHf' 
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
		
			lr_think_time(24);
			
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
				"Name=login.x", "Value=29", ENDITEM,
				"Name=login.y", "Value=13", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				LAST);
	
		lr_end_transaction("login",LR_AUTO);
	
		lr_start_transaction("flights");
	
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(19);
			
			web_reg_find("Fail=NotFound",
				"Text=User has returned to the search page",
				LAST);
		
			web_url("Search Flights Button", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
				"TargetFrame=body", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
				"Snapshot=t3.inf", 
				"Mode=HTML", 
				LAST);
		
		lr_end_transaction("flights",LR_AUTO);
	
		lr_start_transaction("find_flights");
	
			web_add_header("Origin", 
				"http://localhost:1080");
		
			lr_think_time(63);
		
		/*Correlation comment - Do not change!  Original value='132;577;09/14/2020' Name ='outboundFlight' Type ='ResponseBased'*/
			web_reg_save_param_attrib(
				"ParamName=outboundFlight",
				"TagName=input",
				"Extract=value",
				"Name=outboundFlight",
				"Ordinal=ALL",
				"Type=radio",
				SEARCH_FILTERS,
				"IgnoreRedirections=No",
				LAST);
		
			web_reg_save_param("flight_id",         
				"LB=name=\"outboundFlight\" value=\"",
				"RB=;",
				"Ord=ALL",
				LAST);
		
			web_reg_save_param("flight_time",
				"LB=<td align=\"center\">",
				"RB=m<td align=\"center\">",
				"Ord=ALL",
				LAST);

			web_reg_find("Fail=NotFound",
				"Text=<B>{depart}</B> to <B>{arrive}</B> on <B>{departDate}</B>",
				LAST);
		
			web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={depart}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arrive}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=59", ENDITEM, 
				"Name=findFlights.y", "Value=11", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);
	
		lr_end_transaction("find_flights",LR_AUTO);
				
		random = rand()%(atoi(lr_eval_string("{flight_id_count}")) - 1) + 1;
			
		sprintf(flight_time, "{flight_time_%d}", random);
		lr_save_string(lr_eval_string(flight_time), "flight_time_id");
			
		sprintf(flight_id, "{flight_id_%d}", random);
		lr_save_string(lr_eval_string(flight_id), "flight_num_id");
		
		sprintf(outbound_flight, "{outboundFlight_%d}", random);
		lr_save_string(lr_eval_string(outbound_flight), "outboundFlight");
	
		lr_start_transaction("choose_flight");
	
			web_add_auto_header("DNT", 
				"1");
		
			web_add_auto_header("Origin", 
				"http://localhost:1080");
		
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(58);
			
			web_reg_find("Fail=NotFound",
			"Text=Payment Details",
			LAST);
		
			web_submit_data("reservations.pl_2",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t5.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
				"Name=numPassengers", "Value=1", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=reserveFlights.x", "Value=53", ENDITEM,
				"Name=reserveFlights.y", "Value=8", ENDITEM,
				LAST);
	
		lr_end_transaction("choose_flight",LR_AUTO);
	
		lr_start_transaction("buying_flights");
	
			web_revert_auto_header("Origin");
		
			web_revert_auto_header("Upgrade-Insecure-Requests");
		
			lr_think_time(43);

			web_reg_find("Fail=NotFound",
				"Text={departDate} :  {flight_time_id}m : Flight {flight_num_id} leaves {depart}  for {arrive}",
				LAST);

			web_submit_data("reservations.pl_3",
				"Action=http://localhost:1080/cgi-bin/reservations.pl",
				"Method=POST",
				"TargetFrame=",
				"RecContentType=text/html",
				"Referer=http://localhost:1080/cgi-bin/reservations.pl",
				"Snapshot=t6.inf",
				"Mode=HTML",
				ITEMDATA,
				"Name=firstName", "Value={firstName}", ENDITEM,
				"Name=lastName", "Value={lastName}", ENDITEM,
				"Name=address1", "Value={address1}", ENDITEM,
				"Name=address2", "Value={address2}", ENDITEM,
				"Name=pass1", "Value={pass1}", ENDITEM,
				"Name=creditCard", "Value={creditCard}", ENDITEM,
				"Name=expDate", "Value={expDate}", ENDITEM,
				"Name=oldCCOption", "Value=", ENDITEM,
				"Name=numPassengers", "Value={numPassengers}", ENDITEM,
				"Name=seatType", "Value={seatType}", ENDITEM,
				"Name=seatPref", "Value={seatPref}", ENDITEM,
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
				"Name=advanceDiscount", "Value=0", ENDITEM,
				"Name=returnFlight", "Value=", ENDITEM,
				"Name=JSFormSubmit", "Value=off", ENDITEM,
				"Name=buyFlights.x", "Value=30", ENDITEM,
				"Name=buyFlights.y", "Value=11", ENDITEM,
				"Name=.cgifields", "Value=saveCC", ENDITEM,
				LAST);
	
		lr_end_transaction("buying_flights",LR_AUTO);
		
		lr_start_transaction("itinerary");
	
			web_add_auto_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(15);
			
			web_reg_find("Fail=NotFound",
			"Text= User wants the intineraries",
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
	
		lr_start_transaction("logout");
	
			web_add_header("Upgrade-Insecure-Requests", 
				"1");
		
			lr_think_time(16);
			
			web_reg_find("Fail=NotFound",
			"Text=Username",
			LAST);

			web_url("welcome.pl", 
				"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
				"TargetFrame=", 
				"Resource=0", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
				"Snapshot=t7.inf", 
				"Mode=HTML", 
				LAST);
	
		lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC_5_Buying_And_Itinerary",LR_AUTO);

	return 0;
}
async function get_ports() {
	let port = await eel.ports_availabe()();
	if(port == 1){
		alert("Error: no devices found");
	}
	else{
		document.getElementById('ports').value = port;
	}
}


async function set_new_port() {
	var port = document.getElementById('port_set').value;
	if (document.getElementById("port_set").value.length != 0){
		let message = await eel.set_port(port)();
		if(message == 1){
			alert("Error: wrong port")
		}
	}
}


async function get_set_color(){
	var color = document.getElementById("color_picker").value;
	eel.get_set_color(color);
}

async function get_rainbow(){
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0){
		speed = 20;
		document.getElementById("speed").value = 20;
	}
	if (speed < 20) {
		speed = 20;
		document.getElementById("speed").value = 0;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	
	var size = document.getElementById("size").value;
	if (document.getElementById("size").value.length == 0) {
		size = 7;
		document.getElementById("size").value = 7;
	}
	if (size < 1) {
		size = 1;
		document.getElementById("size").value = 0;
	}
	if (size > 20) {
		size = 20;
		document.getElementById("size").value = 20;
	}
	
	eel.get_rainbow(speed, size);
}

async function get_gradient(){
	var color1 = document.getElementById("color_picker1").value;
	var color2 = document.getElementById("color_picker2").value;
	eel.get_gradient(color1, color2);
}

async function get_strobe(){
	var color = document.getElementById("color_picker").value;
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30;
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_strobe(color, speed);
}

async function get_matrix(){
	var color = document.getElementById("color_picker").value;
	var speed = document.getElementById("speed").value;
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_matrix(color, speed);
}

async function get_brightness(){
	var val = document.getElementById("slider").value
	eel.get_brightness(val);
}

async function get_police_siren(){
	if (document.getElementById("blue").checked){
		var type = 0;
	}
	else{
		var type = 1;
	}
		
	var speed = document.getElementById("speed").value
	if (document.getElementById("speed").value.length == 0) {
		speed = 100;
		document.getElementById("speed").value = 100;
	}
	if (speed < 30) {
		speed = 30;
		document.getElementById("speed").value = 30;
	}
	if (speed > 255) {
		speed = 255;
		document.getElementById("speed").value = 255;
	}
	eel.get_police_siren(speed, type);
}
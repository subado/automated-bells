getData("/tables").then(data => {
	const list = document.querySelector("#list");

	data.forEach(element => {
		list.innerHTML += `
			<li>
				<input type="button" class="link" value="${element}">
				<input type="radio" name="table" value="${element}">
			</li>`
	});
	addListener("input.link", "click", (event) => {
		button = event.target;
		localStorage.setItem("table", button.value);
		window.location.href = "/table";
	});
	addListener("input[name=table][type=radio]", "change", (event) => {
		radio = event.target;
		sendData("/shedule", JSON.stringify(radio.value));
	});
});

getData("/shedule").then(data => {
	if (data != "")
	{
		document.querySelector(`input[type=radio][value=${data}]`).checked = true;
	}
})

function updateTime() {
	getData("/time").then(data => {
		document.querySelector("#time").innerHTML = data;
	});
}

updateTime();
setInterval(updateTime, 60 * 1000);

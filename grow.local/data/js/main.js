var app = new Vue({
	el: "#app",
	data: {
		networks: null
	},
	mounted() {
		axios.get("http://grow.local/scan").then(response => {
			this.networks = response.data;
		});
	},
})
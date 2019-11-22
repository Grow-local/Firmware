var app = new Vue({
	el: "#app",
	data: {
		password: "",
		selectedNetwork: {},
		networks: [],
		loading: false
	},
	methods: {
		getNetworks: function () {
			this.loading = true;
			axios.get("http://grow.local/scan").then(response => {
				this.networks = response.data;
			}).finally(() => {
				this.loading = false;
			});
		});
	},
	mounted() {
		this.getNetworks();
	},
})
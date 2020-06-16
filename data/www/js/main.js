var app = new Vue({
	el: "#app",
	data: {
		password: "",
		selectedNetwork: {},
		networks: [],
		loading: false,
		submitted: false
	},
	methods: {
		getNetworks() {
			this.loading = true;
			axios.get("http://grow.local/scan").then((response) => {
				this.networks = response.data;
			}).finally(() => {
				this.loading = false;
			});
		},
		joinNetwork() {
			this.submitted = true;
			axios.post("http://grow.local/join", { ssid: this.selectedNetwork.ssid, password: this.password }).then(() => {

			});
		}
	},
	mounted() {
		this.getNetworks();
	},
});

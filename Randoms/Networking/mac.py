import requests

def get_mac_details(mac_address):
    url = f"https://api.maclookup.app/v2/macs/{mac_address}"
    
    try:
        response = requests.get(url)
        if response.status_code == 200 and response.json().get('found') == True:
            data = response.json()
            
            company = data.get('company', 'Unknown')
            reg_date = data.get('updated', 'No date available')
            
            print(f"Company: {company}")
            print(f"Registration/Start Date: {reg_date}")
        elif response.status_code != 200:
            print(f"Error: Received status code {response.status_code}")
        else:
            print("MAC address not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

mac = "02:50:6F:D6:5C:38"
get_mac_details(mac)
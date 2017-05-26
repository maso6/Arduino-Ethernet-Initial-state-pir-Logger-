# Arduino-Ethernet-Initial-state-pir-Logger-
Dette inlæg viser et eksempel på hvordan man sende data til Initialstate.com. Initial state er et godt alternativ hvis du ikke har det store kendskab til MySql og databaser generelt. Med Initial State får man et grafisk interface hvor ens logninger bliver vist via grafer. Alle målinger bliver vist i realtid hvilket betyder at man har mulighed for at benytte systemet til en infoskærm.

# Step 1
Som vist på billedet, give Initial state en flot graf over de events som vi logger med en Arduino Uno + Ethernet Shield. Via en pir sensor kan vi måle fx. hvor mange gange man benytter sig af et gæsteværelse eller hvor mange gange lyset i garagen bliver aktiveret.

Selvom mit projekt har fokus på en pir sensor som giver et fast signal på “1”. kan man sagtens gå ind og sende flere værdier med fx. temperatur, fugtighed, co2 niveau og via forbrug om pæren er sprunget. Med en frekvens fx. hvert 10 min. 

Så i stedet for et kald hver gang en kontakt bliver aktiveret, kan man automatisk måle værdien på fx. en temperaturføler og sende det til Initial State hvert 5 min. 

# Step 2
Denne kode virker kun til Arduino med Ethernet Shield, jeg anbefaler kraftigt at købe et orginalt shield fra Arduino da jeg har haft dårlig erfaringer med Kina kopier. Man kan sagtens finde et billigt originalt shield til under 150kr. 

Den første del af koden henter de bibloteker vi skal bruge som er standard i Arduino. Hvilket betyder at i ikke behøver at hente dem eksternt og installere dem. 

Den anden del af koden er selve opkoblingen til Initialstate.com hvor vi benytter os af vores bucketKey, BucketName og accessKey. 

Husk at opret et signal i det pågældende skema. I mit tilfælde hedder det “Signal 1”. Efter vi har angivet indstillingerne til Initial state bliver pir sensoren angivet om indgang og får en værdi “LOW”. 

I bunden af filen ligger funktionen postData() som er den funktion der laver en connection til Initial State via json. Derudover tjekker den om forbindelsen er etableret ellers skriver den fejl. 

# Step 3
Det færdige resultat ser således ud og virker upåklageligt. Husk at indstil hvor bred sensoren skal måle samt hvor lang tid signalet skal være aktivt på pir sensoren. Derudover er det vigtigt at man sikre sig at Jord og +5 volt er placeret korrekt så sensoren ikke bliver brændt af.  

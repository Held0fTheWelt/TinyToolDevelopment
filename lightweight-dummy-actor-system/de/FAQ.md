# FAQ

## Was macht LightweightDummyActorSystem?

Es bietet einen Runtime-Dienst für Dummy-Aktor-Workflows, einschließlich der Registrierung von Subjekten, der Vertretung durch Dummy-Aktoren, Übergängen zwischen Beförderung und Degradierung, Diagnosefunktionen, einem Editor-Inspektor und einem Validate-Commandlet.

## Kann es ohne andere Tiny-Tool-Plugins verwendet werden?

Ja. Die Module Runtime, Editor und DeveloperTool sind als Kernpaket implementiert. Die Adapter für WarCollection, LightningCore, UCM, PIO und BPJ sind optionale, zielplattform-spezifische Integrationen und für das ausgelieferte Kernverhalten nicht erforderlich.

## Welche Engine-Versionen werden unterstützt?

Die ausgelieferte Release-Matrix zielt auf Unreal Engine 5.4 bis 5.8 für Win64, Linux und Mac ab, soweit die Module-Allow-Lists diese Plattformen erlauben.

## Ändert es Projektassets eigenständig?

Nein. Der Kern-Dienst verwaltet die Repräsentation und den Übergangszustand. Jegliche projektspezifische Änderung oder Adapter-Verhalten sollte im jeweiligen Projekt-Workflow überprüft werden.

## Wo erhalte ich Support?

Nutzen Sie den Support-Link auf der Fab-Produktseite.

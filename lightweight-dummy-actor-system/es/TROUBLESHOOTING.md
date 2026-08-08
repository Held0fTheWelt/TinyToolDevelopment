---
lang: es
title: LightweightDummyActorSystem Troubleshooting
audience: [end_user]
owner_ref: plugin:LightweightDummyActorSystem
applies_to:
  component: LightweightDummyActorSystem
symptom: RegisterSubject fails or QueryReadiness returns a non-Ready status with issues.
recovery:
  steps:
    - Confirm the plugin is enabled under Edit > Plugins and restart the editor
    - Re-read the matching troubleshooting entry and apply the documented fix
    - Re-run the quick start smoke check
version:
  since: "1.0"
---
# Solución de problemas

Formato: Síntoma → Causa → Solución.

## 0. Lo habilité y no pasó nada

**Síntoma:** Tras habilitar `LightweightDummyActorSystem` y reiniciar, no aparecen actores dummy ni se ejecuta por sí solo ningún flujo de trabajo del producto Tiny Tools.  
**Causa:** LDAS es un paquete de API/servicio. Los sujetos se registran a través de `ULDASWorldSubsystem`; nada se genera automáticamente sin un perfil y una llamada de registro.  
**Solución:** Crea un Activo de Datos `ULDASRepresentationProfile` y ejecuta el ejemplo de trabajo de registro + `QueryReadiness` en [QUICKSTART.md](QUICKSTART.md).

## 1. `RegisterSubject` devuelve false

**Síntoma:** El registro falla para un nuevo ID de sujeto.  
**Causa:** ID de sujeto inválido o duplicado, o descriptor/perfil rechazado por el registro del subsistema.  
**Solución:** Verifica que los campos de `FLDASSubjectId` estén completos y sean únicos; confirma que el activo del perfil esté cargado; reintenta después de `UnregisterSubject` si se está reemplazando.

## 2. El estado de disponibilidad no es Ready

**Síntoma:** `QueryReadiness` devuelve `Warning` o un estado bloqueante con problemas.  
**Causa:** Los proveedores de disponibilidad requeridos fallaron, o las entradas de política (distancia/enfriamiento) no se cumplen.  
**Solución:** Inspecciona las advertencias/problemas de `FLDASReadinessReport`; ajusta las distancias, el enfriamiento o `RequiredReadinessProviders` en `ULDASRepresentationProfile`; resuelve los fallos de los proveedores antes de promover.

## 3. La promoción falla de forma cerrada (closed)

**Síntoma:** `RequestPromotion` no avanza la representación cuando `bFailClosedOnPromotionFailure` es true.  
**Causa:** El perfil solicita un comportamiento de fallo cerrado ante un error de promoción.  
**Solución:** Corrige primero el fallo subyacente de disponibilidad/política. Solo desactiva `bFailClosedOnPromotionFailure` cuando se acepte intencionalmente un fallo suave.

## 4. Promoción en tiempo de ejecución rechazada

**Síntoma:** Las solicitudes de promoción son no-op mientras que la despromoción sigue funcionando.  
**Causa:** `bAllowRuntimePromotion` es false en el perfil.  
**Solución:** Habilita `bAllowRuntimePromotion` en `ULDASRepresentationProfile` cuando se desee una promoción en tiempo de ejecución.

## 5. El inspector del editor no muestra sujetos

**Síntoma:** La interfaz de usuario del inspector está vacía después de PIE o del trabajo en el mundo del editor.  
**Causa:** Los sujetos nunca se registraron en ese subsistema de mundo, o se está inspeccionando el contexto de mundo incorrecto.  
**Solución:** Confirma el registro contra el mismo `UWorld` que observa el inspector; vuelve a registrar después de recargar el mapa.

## 6. El commandlet de validación informa errores de contrato

**Síntoma:** `ULDASValidateContractsCommandlet` sale con hallazgos.  
**Causa:** Incoherencias entre perfil/descriptor/contrato en el contenido del proyecto.  
**Solución:** Lee la salida del commandlet, corrige los activos nombrados y vuelve a ejecutar la validación.

## 7. Se esperan puentes de WarCollection / Lightning / UCM

**Síntoma:** Las APIs de adaptador opcionales parecen faltar.  
**Causa:** Esos puentes son específicos de destino y no forman parte de MVP 1+2+3.  
**Solución:** Utiliza únicamente las APIs centrales incluidas. Considera los adaptadores como integraciones opcionales futuras.

## Documentos relacionados

- [QUICKSTART.md](QUICKSTART.md)
- [UserManual.md](UserManual.md)
- [SettingsReference.md](SettingsReference.md)
- [FAQ.md](FAQ.md)

<!-- doc-provenance: AKDB:plugins/VisualFidelityDirector/architecture.md; docs/architecture/plugins/VisualFidelityDirector/product-facts.yml; reconciled 2026-07-12 -->
# Preguntas frecuentes

## ¿VFD reemplaza el renderizador o el anti-aliasing de Unreal?

No. Es una capa de diagnóstico, perfil, evidencia, comparación, receta, prueba, escáner y recomendación por encima de los sistemas de renderizado existentes de Unreal.

## ¿Qué cambió en la versión 2.0.0?

La versión `2.0.0` agrega el cockpit centrado en perfiles (selector de variantes, ruta de herencia, procedencia, hallazgos, comparación de perfiles, aplicación permanente gobernada, métricas en vivo multicuadro), `UVFDCockpitBlueprintLibrary` y activos de demostración de Blueprint empaquetados. La página integrada de Expert Tools conserva el flujo de trabajo de capturas y recetas de 1.x.

## ¿Requiere IA o servicios en la nube?

No. VFD no tiene requisitos de IA externa, nube, Python, Node.js ni cuentas.

## ¿Necesita otros complementos de Tiny Tool?

No. El flujo de trabajo principal es autónomo.

## ¿A qué versión de Unreal está dirigido?

Visual Fidelity Director es compatible con Unreal Engine 5.4 a 5.8 a través del descriptor de rama de motor correspondiente y permite Win64, Linux y Mac.

## ¿Puede modificar mi proyecto?

Por defecto, no. La aplicación permanente gobernada solo puede escribir en tres destinos de configuración cuando los aprueba explícitamente: grupos de Scalability en `DefaultGameUserSettings.ini`, configuración del renderizador en `DefaultEngine.ini` y Device Profiles en `DefaultDeviceProfiles.ini`. Expert Tools **Preview Apply + Rollback** puede establecer temporalmente las CVar de sesión del editor compatibles y luego restaurarlas. Los activos, materiales, Post Process Volumes y preajustes MRQ no se mutan.

## ¿Lumen Deep Scan cambia mallas o materiales?

No. El escaneo profundo de Lumen escribe hallazgos de revisión a partir de metadatos de capturas y Asset Registry. No cambia la configuración de tarjetas de malla estática, grafos de materiales, banderas de uso compartido de tarjetas de materiales, configuración de proyecto ni preajustes MRQ.

## ¿Captura capturas de pantalla?

El flujo de trabajo A/B de Expert Tools escribe informes de comparación solo de metadatos, a menos que un flujo de trabajo futuro proporcione rutas de capturas de pantalla. Use informes para vincular decisiones y capturar evidencia visual manualmente cuando sea necesario.

## ¿Por qué algunos hallazgos tienen "Confianza media"?

Muchos artefactos visuales dependen del contenido y del movimiento. VFD separa los hechos de las heurísticas para que pueda enrutar la revisión manual sin tratar los metadatos como prueba.

## ¿A dónde van los perfiles y los informes?

```text
Saved/VisualFidelityDirector/profiles/
Saved/VisualFidelityDirector/reports/
Saved/VisualFidelityDirector/recipes/
```

## ¿Puedo usar VFD desde Blueprints?

Sí. `UVFDCockpitBlueprintLibrary` expone funciones de perfil, evidencia, capacidad y aplicación gobernada. Consulte `Content/Blueprints/BPF_VFD_API` para obtener ejemplos conectados.

## ¿A quién contacto para obtener soporte?

Utilice el correo electrónico de soporte que figura en el descriptor del complemento:
`support@tiny-tool-development.com`.

Discord: `#support` (consulte la lista de productos cuando se publique).

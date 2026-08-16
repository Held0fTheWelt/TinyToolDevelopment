<!-- doc-provenance: AKDB:plugins/SmartContentDiet/architecture.md; docs/architecture/plugins/SmartContentDiet/product-facts.yml; reconciled 2026-07-16 -->
# Preguntas frecuentes

**¿Smart Content Diet requiere IA, una cuenta u otro plugin?**
No. El ciclo principal (escanear → revisar → aplicar correcciones seguras → volver a escanear → medir) se ejecuta completamente en el editor
sin necesidad de servicios de IA, cuentas ni plugins de terceros. Existen rutas opcionales del ecosistema a través de **Unreal Capability
Mesh (UCM)**, pero nunca son obligatorias.

**¿Es seguro ejecutarlo?**
El escaneo y la vista previa son de solo lectura. Aplicar correcciones, reducciones, movimientos o eliminaciones **modifica los activos del proyecto** — hágalo únicamente en un espacio de trabajo desechable, respaldado y con control de versiones. Las rutas de mutación están protegidas por aprobación de forma predeterminada. Úselo bajo su propio riesgo.

**¿Qué versiones del motor son compatibles?**
Unreal Engine 5.4+. Es un plugin del editor.

**¿Cuál es la diferencia entre los escaneos Quick Safe, Full y Deep?**
Quick Safe utiliza únicamente el registro y los metadatos (sin cargar activos, rápido). Full carga los activos para obtener hallazgos accionables de malla/textura/material. Deep añade métricas profundas de materiales y mallas estáticas, y es el más lento.

**¿Por qué no puedo ver las pestañas Preset o Governance?**
Son pestañas avanzadas (Ingeniero / Productor). Cambie el rol en Configuración o en la cabecera.

**¿Puedo ejecutarlo en CI / headless?**
Sí. Un commandlet admite `-QuickSafe` / `-FullScan` / `-DeepScan`, `-OptimizationQueueReport` y
`-ApplySafeQueue` (aplicar solo en proyectos respaldados).

**¿Incluye software de terceros?**
No. Consulte [THIRD_PARTY_SOFTWARE.md](THIRD_PARTY_SOFTWARE.md).

**¿Dónde puedo obtener soporte?**
Utilice el enlace de soporte en la página del producto de Fab.

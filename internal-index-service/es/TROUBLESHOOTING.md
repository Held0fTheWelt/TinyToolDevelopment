<!-- doc-provenance: SAD architecture.md sections 6,8,10,11; facts product-facts.yml; reconciled 2026-07-16 -->
# Solución de problemas

## El build falla en UE 5.6 con errores de encabezado del motor

Asegúrese de que los módulos de IIS compilen con C++20. Los encabezados del motor UE 5.6 utilizan sintaxis C++20. Los archivos `.Build.cs` de IIS deben incluir:

```csharp
CppStandard = CppStandardVersion.Cpp20;
```

## La búsqueda no devuelve resultados

Compruebe:

- que los fragmentos preparados fueron importados
- que el catálogo fue reconstruido
- que el texto de la consulta no esté vacío
- que el estado del ciclo de vida esté activo
- que la raíz del índice apunte a la carpeta del proyecto esperada

## La búsqueda vectorial no devuelve resultados

Compruebe:

- que se crearon tareas de embedding
- que las tareas de embedding se ejecutaron correctamente
- que la ruta/ejecutor de LLM Store esté registrado
- que la configuración del backend vectorial coincida con los artefactos persistidos

## La importación falla

Compruebe que el archivo JSONL de fragmentos preparados exista y sea legible. Revise los informes de importación bajo la raíz Saved de IIS para verificar advertencias de validación y registros rechazados.

## El índice HNSW no se puede cargar o genera advertencias del backend

Si el backend HNSW no se puede cargar o aparecen advertencias del backend tras cambiar la configuración de almacenamiento vectorial, cambie temporalmente a `jsonl_bruteforce` para separar los problemas de datos vectoriales de los problemas de indexación específicos del backend. Mantenga **Rebuild On Vector Format Mismatch** habilitado para que las particiones HNSW persistentes incompatibles se reconstruyan a partir de los vectores origen en lugar de cargarse con un diseño de bytes incorrecto.

Confirme que `Source/ThirdParty/hnswlib` esté presente en el paquete y vuelva a crear los artefactos vectoriales tras cambiar **Vector Storage Format**.

## El ajuste en tiempo de ejecución o comando del índice devuelve "Disabled"

Compruebe **Enable Runtime Control Mutations** en la configuración del proyecto. Cuando está desactivado, las consultas de lectura como `iis.control.state` siguen funcionando, pero los comandos de tune, act, persist y reset devuelven una respuesta de desactivado por diseño.

Vuelva a habilitar la configuración para comandos de modificación o continúe con instrucciones de estado y diagnóstico en solo lectura.

## Faltan herramientas de agente en el cliente MCP

Compruebe:

- que Unified MCP Server esté habilitado y ejecutándose
- que Unreal Capability Mesh esté habilitado
- que la configuración del proyecto incluya manifiestos de rutas de agentes IIS (`iis.agent.*.v1`)
- llame a `mesh_list_routes` o `mesh_reload_setup` y actualice el cliente MCP
- que IIS pueda escribir contratos de herramientas de agentes
- que el cliente MCP esté conectado al endpoint de UMCP y no a un servidor MCP heredado por plugin

Actualice la configuración de Capability Mesh y vuelva a conectar o actualizar el cliente MCP tras realizar cambios en las rutas.

## La herramienta de agente devuelve salvaguardas de solo lectura

Es el comportamiento esperado. Las respuestas de IIS indican intencionadamente que no se permiten modificaciones en el proyecto.

## La autocomprobación de rendimiento informa una desviación

Revise el último resultado de rendimiento en `iis.perf.last` o vuelva a ejecutar `iis.perf.run`. Las desviaciones suelen indicar que la carga de trabajo vectorial actual, el backend o el ajuste superan los presupuestos configurados.

Reduzca primero la amplitud de la consulta o la carga de trabajo vectorial. Actualice los presupuestos solo tras una validación representativa en la máquina o perfil de proyecto de destino.

## Dónde consultar los informes

Ubicaciones predeterminadas:

```text
Saved/InternalIndexService/reports
Saved/InternalIndexService/imports
Saved/InternalIndexService/agent_contracts
```

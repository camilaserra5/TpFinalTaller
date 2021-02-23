--Revisa en un rango si hay enemigos en el mapa
--los jugadores aparecen con numeros mayores o iguales a 10-- macro Variable
next_position = {
    [0] = "a", -- IZQUIERDA
    [1] = "w", -- ADELANTE
    [2] = "d", -- DERECHA
    [3] = "s" -- RETROCEDER
}

function estoy_en_el_borde(pos_x, pos_y)
    if (pos_y >= #mapa[1] or pos_x >= #mapa) then
        return true
    end
    if (pos_x <= 1 or pos_y <= 1) then
        return true
    end
    return false
end


--Funcion que verifica si puede avanzar
--Nota: to do lo que sea distinto a 'false' 'nil' es tomado como true;
function proximo_movimiento(pos_x, pos_y)
    if (estoy_en_el_borde(pos_x, pos_y)) then
        return next_position[2]
    end
    if (mapa[pos_x][pos_y + 1] == 0) then
        return next_position[1]
    end
    if (mapa[pos_x][pos_y - 1] == 0) then
        return next_position[3]
    end
    if (mapa[pos_x - 1][pos_y] == 0) then
        return next_position[0]
    end
    if (mapa[pos_x + 1][pos_y] == 0) then
        return next_position[2]
    end
end

function posicion_enemigo_cerca(posPixelX, posPixelY, cantJugadores, tablaEnemigos)
    local rango = 10
    for i = 1, cantJugadores, 2 do
        local enemigoX = tablaEnemigos[i]
        local enemigoY = tablaEnemigos[i + 1]
        local diferencia_x = enemigoX - posPixelX
        local diferencia_y = enemigoY - posPixelY
        if (diferencia_x < 21 and diferencia_x > -21) then
            if (diferencia_y < 21 and diferencia_y > -21) then
                print("======ENEMIGO CERCA======")
                return {enemigoX, enemigoY}
            end
        end
    end
    return nil
end

function disparar_al_enemigo()
    print("piumpium")
    return 'p'
end

function crear_accion(pos_x, pos_y, cantJugadores, posPixelX, posPixelY, tablaEnemigos)
    local siguiente_mov = proximo_movimiento(pos_x, pos_y)
    local posicion_enemigo = posicion_enemigo_cerca(posPixelX, posPixelY, cantJugadores, tablaEnemigos)
    if (posicion_enemigo) then
        return disparar_al_enemigo()
    end
    return siguiente_mov
end